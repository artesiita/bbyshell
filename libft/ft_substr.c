/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:37:13 by bcanals-          #+#    #+#             */
/*   Updated: 2024/07/04 18:41:12 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rtrn;

	rtrn = malloc(1);
	if (rtrn == NULL)
		return (NULL);
	*rtrn = 0;
	if (start > ft_strlen(s))
		return (rtrn);
	if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	free(rtrn);
	rtrn = malloc(len + 1);
	if (rtrn == NULL)
		return (NULL);
	s += start;
	ft_memmove(rtrn, s, len + 1);
	rtrn[len] = 0;
	return (rtrn);
}
