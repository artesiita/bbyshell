#include "../../inc/minishell.h"


t_token	*tokenize(char *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->quote = Q_NONE;
	new->type = T_WORD;
	new->next = NULL;
	return (new);
}

void	split_to_tokens(t_token *tok, t_expan *expan)
{
	char	**split;
	t_token	*next_save;
	t_token	*new;
	int		i;

	split = ft_split(expan->val, ' ');
	next_save = tok->next;
	if (!split || !split[0])
		return (free(tok->content), tok->content = ft_strjoin(expan->pre, expan->suf), (void)free_split(split));
	free(tok->content);
	tok->content = ft_strjoin(expan->pre, split[0]);
	i = 0;
	while (split[++i])
	{
		new = tokenize(split[i]);
		new->next = next_save;
		tok->next = new;
		tok = new;
	}
	expan->tmp = tok->content;
	tok->content = ft_strjoin(expan->tmp, expan->suf);
	free(expan->tmp);
	free_split(split);
}

char	*expand_to_str(t_mini *mini, char *str, int *dollar_idx, int i)
{
	t_expan expan;

	expan.pre = ft_substr(str, 0, *dollar_idx);
	if (str[*dollar_idx + 1] == '?')
	{
		expan.val = ft_itoa(mini->exit_status);
		i = *dollar_idx + 2;
	}
	else
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		expan.tmp = ft_substr(str, *dollar_idx + 1, i - (*dollar_idx + 1));
		expan.val = get_env_value(expan.tmp, mini->env_head);
		if (!expan.val)
			expan.val = ft_strdup("");
		else
			expan.val = ft_strdup(get_env_value(expan.tmp, mini->env_head));
		free(expan.tmp);
	}
	expan.suf = ft_strdup(&str[i]);
	expan.tmp = ft_strjoin(expan.pre, expan.val);
	expan.res = ft_strjoin(expan.tmp, expan.suf);
	*dollar_idx = ft_strlen(expan.pre) + ft_strlen(expan.val);
	return (free(expan.pre), free(expan.val), free(expan.suf), free(expan.tmp), expan.res);
}

void    expand_to_tokens(t_mini *mini, t_token *token, int *dollar_idx, int i)
{
    t_expan expan;

	expan.pre = ft_substr(token->content, 0, *dollar_idx);
	if (token->content[*dollar_idx + 1] == '?')
	{
		expan.val = ft_itoa(mini->exit_status);
		i = *dollar_idx + 2;
	}
	else
	{
		while (token->content[i] && (ft_isalnum(token->content[i]) || token->content[i] == '_'))
			i++;
		expan.tmp = ft_substr(token->content, *dollar_idx + 1, i - (*dollar_idx + 1));
		expan.val = get_env_value(expan.tmp, mini->env_head);
		if (!expan.val)
			expan.val = ft_strdup("");
		else
			expan.val = ft_strdup(get_env_value(expan.tmp, mini->env_head));
		free(expan.tmp);
	}
	expan.suf = ft_strdup(&token->content[i]);
	split_to_tokens(token, &expan);
	*dollar_idx = ft_strlen(token->content);
	return (free(expan.pre), free(expan.val), free(expan.suf), (void)0);
}