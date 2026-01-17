/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <bcanals-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:53:34 by bcanals-          #+#    #+#             */
/*   Updated: 2024/07/01 20:39:03 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (size != 0)
	{
		while (dest[i] != 0 && i < size)
			i++;
		while (i < (size - 1) && src[j] != 0)
		{
			dest[i] = src[j];
			i++;
			j++;
		}
		if (i <= size - 1)
			dest[i] = 0;
	}
	while (src[j] != 0)
	{
		i++;
		j++;
	}
	return (i);
}
