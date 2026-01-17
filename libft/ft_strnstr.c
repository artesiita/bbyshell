/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:43:53 by bcanals-          #+#    #+#             */
/*   Updated: 2024/07/04 17:20:18 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[0] == 0)
		return ((char *)(big));
	if (ft_strlen(big) < len)
		len = ft_strlen(big);
	if (ft_strlen(little) > len)
		return (NULL);
	len -= ft_strlen(little);
	while (i <= len)
	{
		if (ft_strcmp(big, little) == 0)
			return ((char *)(big));
		big++;
		i++;
	}
	return (NULL);
}
