/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_to_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:07:09 by lartes-s          #+#    #+#             */
/*   Updated: 2026/05/01 11:43:25 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*tokenize(char *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->type = T_WORD;
	new->next = NULL;
	new->hd = NULL;
	return (new);
}

int	manage_token(t_mini *mini, t_token *tok, t_expan *expan, char **split)
{
	free(tok->content);
	if (!split || !split[0])
	{
		tok->content = ft_strjoin(expan->pre, expan->suf);
		free_split(split);
		filter_expansion(mini, tok, ft_strlen(expan->pre));
		return (1);
	}
	if (expan->val[0] == ' ')
	{
		if (ft_strlen(expan->pre) == 0)
		{
			tok->content = ft_strdup(split[0]);
			return (0);
		}
		else
		{
			tok->content = ft_strdup(expan->pre);
			return (-1);
		}
	}
	else
		tok->content = ft_strjoin(expan->pre, split[0]);
	return (0);
}

void	token_tail(t_mini *mini, t_token *tok, t_expan *expan, t_token *nsave)
{
	t_token	*new;

	if (expan->val[ft_strlen(expan->val) - 1] == ' ')
	{
		tok->content = ft_strdup(expan->tmp);
		free(expan->tmp);
		if (expan->suf && expan->suf[0])
		{
			new = tokenize(expan->suf);
			new->next = nsave;
			tok->next = new;
			filter_expansion(mini, new, 0);
		}
	}
	else
	{
		tok->content = ft_strjoin(expan->tmp, expan->suf);
		filter_expansion(mini, tok, ft_strlen(tok->content)
			- ft_strlen(expan->suf));
		free(expan->tmp);
	}
}

void	split_to_tokens(t_mini *mini, t_token *tok, t_expan *expan)
{
	char	**split;
	t_token	*next_save;
	t_token	*new;
	int		i;

	split = ft_split(expan->val, ' ');
	next_save = tok->next;
	i = manage_token(mini, tok, expan, split);
	if (i == 1)
		return ;
	while (split[++i])
	{
		new = tokenize(split[i]);
		new->next = next_save;
		tok->next = new;
		tok = new;
	}
	expan->tmp = tok->content;
	token_tail(mini, tok, expan, next_save);
	free_split(split);
}

void	expand_to_tokens(t_mini *mini, t_token *token, int *dollar_idx, int i)
{
	t_expan	expan;

	expan.pre = ft_substr(token->content, 0, *dollar_idx);
	if (token->content[*dollar_idx + 1] == '?')
	{
		expan.val = ft_itoa(mini->exit_status);
		i = *dollar_idx + 2;
	}
	else
	{
		while (token->content[i] && (ft_isalnum(token->content[i])
				|| token->content[i] == '_'))
			i++;
		expan.tmp = ft_substr(token->content, *dollar_idx + 1, i - (*dollar_idx
					+ 1));
		expan.val = get_env_dup(expan.tmp, mini->env_head);
		free(expan.tmp);
		if (!expan.val)
			expan.val = ft_strdup("");
	}
	expan.suf = ft_strdup(&token->content[i]);
	split_to_tokens(mini, token, &expan);
	*dollar_idx = ft_strlen(token->content);
	return (free(expan.pre), free(expan.val), free(expan.suf), (void)0);
}
