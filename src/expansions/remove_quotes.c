/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 20:56:37 by lartes-s          #+#    #+#             */
/*   Updated: 2026/05/06 21:44:04 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unmask_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SQ_PLACEHOLDER)
			str[i] = '\'';
		else if (str[i] == DQ_PLACEHOLDER)
			str[i] = '\"';
		i++;
	}
}

char	*mask_expanded_value(char *val)
{
	int	i;

	i = 0;
	if (!val)
		return (NULL);
	while (val[i])
	{
		if (val[i] == '\'')
			val[i] = SQ_PLACEHOLDER;
		else if (val[i] == '\"')
			val[i] = DQ_PLACEHOLDER;
		i++;
	}
	return (val);
}

void	mask_quotes(char *str)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	while (str && str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && q == 0)
			q = str[i];
		else if (str[i] == q)
			q = 0;
		else if (str[i] == '\'' && q == '\"')
			str[i] = SQ_PLACEHOLDER;
		else if (str[i] == '\"' && q == '\'')
			str[i] = DQ_PLACEHOLDER;
		i++;
	}
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
