
#include "../../inc/minishell.h"

char	*remove_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		q;

	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	q = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && q == 0)
			q = str[i];
		else if (str[i] == q)
			q = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	expand_double_quoted(t_mini *mini, t_token *token)
{
	int		i;
	char	*old_str;

	i = 0;
	while (token->content[i])
	{
		if (token->content[i] == '$' && (token->content[i + 1] != ' '
				&& token->content[i + 1] != '\0'))
		{
			old_str = token->content;
			token->content = expand_to_str(mini, token->content, &i, i + 1);
			free(old_str);
		}
		else
			i++;
	}
}
void	quote_flag(char *content, int *q_ctx, int i)
{
	if (content[i] == '\'' && *q_ctx == 0)
		*q_ctx = 1;
	else if (content[i] == '\"' && *q_ctx == 0)
		*q_ctx = 2;
	else if ((content[i] == '\'' && *q_ctx == 1) || (content[i] == '\"'
			&& *q_ctx == 2))
		*q_ctx = 0;
}

void	expand_non_quoted(t_mini *mini, t_token *tok, int i)
{
	int		q_ctx;
	char	*old;

	q_ctx = 0;
	while (tok->content && tok->content[i])
	{
		quote_flag(tok->content, &q_ctx, i);
		if (tok->content[i] == '$' && q_ctx != 1 && tok->content[i + 1])
		{
			if (tok->content[i + 1] == ' ' || tok->content[i + 1] == '\0')
			{
				i++;
				continue ;
			}
			if (q_ctx == 0)
				expand_to_tokens(mini, tok, &i, i + 1);
			else
			{
				old = tok->content;
				tok->content = expand_to_str(mini, tok->content, &i, i + 1);
				free(old);
			}
		}
		else
			i++;
	}
}

int	expansions(t_mini *mini)
{
	t_token *cur;
	char *clean_content;

	cur = mini->tokens;
	while (cur)
	{
		if (cur->type == T_WORD && cur->quote != Q_SINGLE)
		{
			if (cur->quote == Q_DOUBLE)
				expand_double_quoted(mini, cur);
			else
				expand_non_quoted(mini, cur, 0);
		}
		if (cur->type == T_WORD)
		{
			clean_content = remove_quotes(cur->content);
			free(cur->content);
			cur->content = clean_content;
		}
		cur = cur->next;
	}
	return (0);
}