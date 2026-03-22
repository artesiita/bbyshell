/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:48:49 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/22 16:48:55 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstlast(void *lst)
{
	void	*last;

	last = lst;
	while (lst)
	{
		last = lst;
		lst = *(void **)lst;
	}
	return (last);
}
