/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 03:40:22 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/22 17:09:02 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	ft_lstclear(void **lst, void (*del)(void *))
{
	void	*node;
	void	*next;

	if (!lst || !del || !*lst)
		return ;
	node = *lst;
	while (node)
	{
		next = *(void **)node;
		ft_lstdelone(node, del);
		node = next;
	}
	*lst = NULL;
}
