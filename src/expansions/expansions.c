
#include "../../inc/minishell.h"

char	*get_variable(char *str, int dollar, t_mini *mini)
{
	char	*prefix;
	char	*sufix;
	char	*key;
	char	*variable;
	int		variable_len;

	variable_len = 0;
	prefix = ft_substr(str, 0, dollar);
	dollar++;
	while (str[dollar] != ' ' && str[dollar] != '\0')
		variable_len++;
	key = ft_substr(str, dollar, variable_len);
	sufix = ft_substr(str, dollar + variable_len, ft_strlen(prefix)
			+ ft_strlen(key));
	variable = get_env_value(key, mini->env_head);
	str = ft_strjoins(prefix, variable, sufix);
}

int	expand_double_quoted(t_token *token)
{
	char	*prefix;
	char	*variable;
	char	*sufix;
	int		i;

	i = 0;
	while (token->content[i])
	{
		if (token->content[i] == '$')
	}
}

int	expansions(t_mini *mini)
{
	t_token *cur;

	cur = mini->tokens;
	if (!cur)
		return (ERROR);
	while (cur)
	{
		if (cur->type == T_WORD && cur->quote != Q_SINGLE
			&& ft_strchr(cur->content, '$'))
		{
			if (cur->quote == Q_DOUBLE)
				expand_double_quoted(cur);
			else
				cur = expand_non_quoted(cur, mini);
		}
		else if (cur->type == T_WORD && (cur->quote == Q_SINGLE
				|| cur->quote == Q_DOUBLE))
			remove_quotes(cur);
		else
			cur = cur->next;
	}
	return (0);
}