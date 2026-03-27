/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:40:43 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/27 16:52:52 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_lstnew(int struct_size, void *content)
{
	void	*rtrn;

	rtrn = malloc(struct_size);
	if (!rtrn)
		return (NULL);
	*(void **)rtrn = NULL;
	ft_memcpy((char *)rtrn + sizeof(void *), &content, sizeof(void *));
	return (rtrn);
}
