/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <bcanals-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:22:44 by bcanals-          #+#    #+#             */
/*   Updated: 2024/07/04 12:50:40 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				retr;
	unsigned int	i;

	i = 0;
	retr = 0;
	while (s1[i] != 0 && s2[i] != 0 && i < n)
	{
		retr = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (retr != 0)
			return (retr);
		i++;
	}
	if (i == n)
		return (retr);
	retr = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (retr);
}
