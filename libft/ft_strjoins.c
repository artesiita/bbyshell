/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:49:18 by bcanals-          #+#    #+#             */
/*   Updated: 2024/12/11 23:55:17 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoins(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*rtrn;

	temp = ft_strjoin(s1, s2);
	rtrn = ft_strjoin(temp, s3);
	free(temp);
	return (rtrn);
}
