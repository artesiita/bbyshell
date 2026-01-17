/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:41:12 by bizcru            #+#    #+#             */
/*   Updated: 2024/07/19 12:42:04 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static unsigned int	count_splits(char const *s, char c)
{
	unsigned int	split_num;

	split_num = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s == c)
		{
			split_num++;
			while (*(++s) == c)
			{
			}
		}
		else
		{
			s++;
			if (!*s)
				split_num++;
		}
	}
	return (split_num);
}

void	clean(char **s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

static char	**fill(char const *s, char c, char **rtrn)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	k = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			return (rtrn);
		while (s[i] && s[i] != c)
			i++;
		rtrn[k] = ft_substr(s, 0, i);
		if (!rtrn[k])
		{
			clean(rtrn);
			return (NULL);
		}
		k++;
		s += i;
		i = 0;
	}
	return (rtrn);
}

char	**ft_split(char const *s, char c)
{
	char			**rtrn;
	unsigned int	size;

	if (!s)
		return (NULL);
	size = count_splits(s, c);
	rtrn = ft_calloc((size + 1), sizeof (char *));
	if (!rtrn)
		return (NULL);
	return (fill(s, c, rtrn));
}
