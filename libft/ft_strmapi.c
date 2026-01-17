/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 03:07:50 by bizcru            #+#    #+#             */
/*   Updated: 2024/07/06 03:19:23 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*rtrn;

	i = 0;
	rtrn = malloc(ft_strlen(s) + 1);
	if (!rtrn)
		return (NULL);
	while (*s)
	{
		rtrn[i] = f(i, *s);
		i++;
		s++;
	}
	rtrn[i] = 0;
	return (rtrn);
}
