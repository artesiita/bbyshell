/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:06:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/05/01 17:27:36 by becanals         ###   ########.fr       */
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
	i = -1;
	j = 0;
	q = 0;
	while (str[++i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && q == 0)
			q = str[i];
		else if (str[i] == q)
			q = 0;
		else
			new[j++] = str[i];
	}
	new[j] = '\0';
	free(str);
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

void	set_inedexes(t_expan *e)
{
	int		i;

	i = e->offset - 1;
	while (e->str[++i])
	{
		if (e->str->r[i] == ''' || e->str[i] == '"' || e->str[i] == '$')
		{
			e->pre_end = i + 1 + e->offset;
			e->type = e->str[i];
			break ;
		}
	}
	while (e->str[++i])
	{
		if (e->str[i] == ''' || e->str[i] == '"' || e->str[i] == '$')
		{
			if (e->type = '$' || e->str[i] == e->type)
			{
				e->exp_end = i - 1 + e->offset;
				break;
			}
		}
	}
}


char	*get_prev(t_expan *e)
{
	char	*prev;

	prev = ft_strndup(e->str[e->offset], e->pre_end + 1);
	if (!prev)
		printf("MALLOC ERROR");
	return (prev);
}

char	*get_exp(t_expan *e)
{
	char	*exp;
	int		offset;
	int		this_strlen;

	offset = e->offset + e->pre_end + 2;
	this_strlen = exp_end - offset;
	exp = ft_strndup(e->str[e->offset], this_strlen);
	if (!exp)
		printf("MALLOC ERROR");
	return (exp);
}

void	do_expansions(t_mini *mini, t_token *tok, int start)
{
	t_expan	expan;

	expan.str = tok->content;
	expan.offset = start;
	set_indexes(&expan);
	expan.pre = get_prev(&expan);
	expan.exp = do_expand(get_exp(&expan), tok);
	if (expan.)
		// funcio que retorna array + gestio de tokens
		// actualitzar l'offset per passarlo a la següent funció
	else
		if (/*dobles*/)
			// Fer l'expansió corresponent
		// Unir la prev amb la exp i amb la següent
		// gestió i neteja de memòria
		// recursivar amb la següent amb l'offset corresponent.
	
	expan.suf = do_expansions(mini, get_suf(&expan));
	free(tok->content);
	tok->content = ft_strjoins(expan.prev, expand.exp, expan.suf);
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
			do_expansions(mini, cur, 0);
			cur->content = clean_content;
		}
		cur = cur->next;
	}
	return (0);
}
