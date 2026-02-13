
#include "../../inc/minishell.h"

void	handle_word(t_token **head, char *input, int *i)
{
	int			start;
	char		quote;
	t_quote_ctx	ctx;

	start = *i;
	quote = 0;
	ctx = Q_NONE;
	if (input[*i] == '\'')
		ctx = Q_SINGLE;
	else if (input[*i] == '\"')
		ctx = Q_DOUBLE;
	while (input[*i])
	{
		if ((input[*i] == '\'' || input[*i] == '\"') && quote == 0)
			quote = input[*i];
		else if (input[*i] == quote)
			quote = 0;
		else if (quote == 0 && (is_space(input[*i])
				|| is_redirection(input[*i])))
			break ;
		(*i)++;
	}
	if (quote != 0)
	{
		printf("syntax error lexer\n"); /*syntax error,
			need to think how to handle (unclosed quotes)*/
		return ;
	}
	add_token(head, ft_substr(input, start, *i - start), T_WORD, ctx);
}

void	handle_redirections(t_token **head, char *input, int *i)
{
	t_token_type	type;
	int				offset;

	offset = 1;
	if (input[*i] == '<')
	{
		type = T_REDIR_IN;
		if (input[*i + 1] == '<')
		{
			type = T_REDIR_HEREDOC;
			offset = 2;
		}
	}
	else
	{
		type = T_REDIR_OUT;
		if (input[*i + 1] == '>')
		{
			type = T_REDIR_APPEND;
			offset = 2;
		}
	}
	add_token(head, ft_substr(input, *i, offset), type, Q_NONE);
	*i += offset;
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
		{
			add_token(&tokens, ft_strdup("|"), T_PIPE, Q_NONE);
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
			handle_redirections(&tokens, input, &i);
		else
			handle_word(&tokens, input, &i);
	}
	return (tokens);
}
