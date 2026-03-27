/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <bcanals-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:22:44 by bcanals-          #+#    #+#             */
/*   Updated: 2026/03/22 17:55:01 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_streq(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] != 0 && s2[i] != 0)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (0);
		i++;
	}
	if ((unsigned char)s1[i] == (unsigned char)s2[i])
		return (1);
	return (0);
}
