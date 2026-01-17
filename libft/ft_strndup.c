/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:38:42 by bizcru            #+#    #+#             */
/*   Updated: 2024/07/05 17:10:31 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*rtrn;
	char	*i;

	if (ft_strlen(s) < n)
		n = ft_strlen(s);
	rtrn = malloc(n + 1);
	if (rtrn == NULL)
		return (NULL);
	i = rtrn;
	while (n-- > 0)
	{
		*i = *s;
		i++;
		s++;
	}
	*i = 0;
	return (rtrn);
}
