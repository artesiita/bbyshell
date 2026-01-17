/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:05:52 by bizcru            #+#    #+#             */
/*   Updated: 2024/07/05 17:38:21 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;

	if (!s1 || !set)
		return ((char *)s1);
	start = 0;
	if (ft_strlen(s1) == 0)
		end = 0;
	else
		end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && s1[start] != 0)
		start++;
	while (ft_strchr(set, s1[end]) && end > start)
		end--;
	return (ft_strndup(&s1[start], end - start + 1));
}
