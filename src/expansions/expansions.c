
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

char	*get_variable(t_mini *mini, char *str, int *dollar_idx, int i)
{
	t_expan	e;

	e.pre = ft_substr(str, 0, *dollar_idx);
	if (str[*dollar_idx + 1] == '?')
	{
		e.val = ft_itoa(mini->exit_status);
		i = *dollar_idx + 2;
	}
	else
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		e.tmp = ft_substr(str, *dollar_idx + 1, i - (*dollar_idx + 1));
		e.val = get_env_value(e.tmp, mini->env_head);
		if (!e.val)
			e.val = ft_strdup("");
		else
			e.val = ft_strdup(e.val);
		free(e.tmp);
	}
	e.suf = ft_strdup(&str[i]);
	e.tmp = ft_strjoin(e.pre, e.val);
	e.res = ft_strjoin(e.tmp, e.suf);
	*dollar_idx = ft_strlen(e.pre) + ft_strlen(e.val);
	return (free(e.pre), free(e.val), free(e.suf), free(e.tmp), e.res);
}

void	expand_double_quoted(t_mini *mini, t_token *token)
{
	int		i;
	char	*old_str;

	i = 0;
	while (token->content[i])
	{
		if (token->content[i] == '$' && (token->content[i + 1] != ' ' && token->content[i + 1] != '\0'))
		{
			old_str = token->content;
			token->content = expand_to_str(mini, token->content, &i, i + 1);
			free(old_str);
		}
		else
			i++;
	}
}

void	expand_non_quoted(t_mini *mini, t_token *tok)
{
	int		i;
	int		q;
	char	*tmp;

	i = 0;
	q = 0;
	while (tok->content && tok->content[i])
	{
		if (tok->content[i] == '\"')
			q++;
		if (tok->content[i] == '$' && tok->content[i + 1] != ' ' 
			&& tok->content[i + 1] != '\0')
		{
			tmp = tok->content;
			if (q % 2 != 0)
				tok->content = get_variable(mini, tmp, &i, i + 1);
			else
				expand_to_tokens(mini, tok, &i, i + 1);
			if (q % 2 != 0)
				free(tmp);
		}
		else
			i++;
	}
}

int	expansions(t_mini *mini)
{
	t_token	*cur;
	char	*tmp;

	cur = mini->tokens;
	while (cur)
	{
		if (cur->type == T_WORD && cur->quote != Q_SINGLE)
		{
			if (cur->quote == Q_DOUBLE)
				expand_double_quoted(mini, cur);
			else
				expand_non_quoted(mini, cur);
		}
		if (cur->type == T_WORD)
		{
			tmp = cur->content;
			cur->content = remove_quotes(tmp);
			free(tmp);
		}
		cur = cur->next;
	}
	return (0);
}