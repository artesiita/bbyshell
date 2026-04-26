/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:30:05 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/26 12:30:22 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_word(t_mini *mini, t_token **head, char *input, int *i)
{
	int			start;
	char		quote;

	start = *i;
	quote = 0;
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
		printf("syntax error: unclosed quotes\n");
		mini->exit_status = 2;
		return (ERROR);
	}
	add_token(mini, head, ft_substr(input, start, *i - start), T_WORD);
	return (SUCCESS);
}

void	handle_redirections(t_mini *mini, t_token **head, char *input, int *i)
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
	add_token(mini, head, ft_substr(input, *i, offset), type);
	*i += offset;
}

t_token	*lexer(t_mini *mini, char *input)
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
			add_token(mini, &tokens, ft_strdup("|"), T_PIPE);
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
			handle_redirections(mini, &tokens, input, &i);
		else
			if (handle_word(mini, &tokens, input, &i) == ERROR)
				return (free_tokens(mini->tokens), NULL);
	}
	return (tokens);
}
