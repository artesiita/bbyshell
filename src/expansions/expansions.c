/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:06:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/03/27 15:42:56 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_to_str(t_mini *mini, char *str, int *dollar_idx, int i)
{
	t_expan	expan;

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
		if (expan.val)
			expan.val = ft_strdup(expan.val);
		else
			expan.val = ft_strdup("");
		free(expan.tmp);
	}
	expan.suf = ft_strdup(&str[i]);
	expan.res = ft_strjoins(expan.pre, expan.val, expan.suf);
	*dollar_idx = ft_strlen(expan.pre) + ft_strlen(expan.val);
	return (free(expan.pre), free(expan.val), free(expan.suf), expan.res);
}

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

void	filter_expansion(t_mini *mini, t_token *tok, int i)
{
	int		q_ctx;
	char	*old;

	q_ctx = 0;
	while (tok->content && tok->content[i])
	{
		quote_flag(tok->content, &q_ctx, i);
		if (tok->content[i] == '$' && q_ctx != 1 && tok->content[i + 1]
			&& (ft_isalnum(tok->content[i + 1]) || tok->content[i + 1] == '_'
				|| tok->content[i + 1] == '?'))
		{
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
	t_token	*cur;
	char	*clean_content;

	cur = mini->tokens;
	while (cur)
	{
		if (cur->type == T_WORD)
		{
			filter_expansion(mini, cur, 0);
			clean_content = remove_quotes(cur->content);
			free(cur->content);
			cur->content = clean_content;
		}
		cur = cur->next;
	}
	return (0);
}
