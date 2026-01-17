/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 04:17:34 by bizcru            #+#    #+#             */
/*   Updated: 2024/07/19 12:52:48 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rtrn;
	t_list	*last;
	t_list	*my_list;

	my_list = lst;
	if (!my_list || !f || !del)
		return (NULL);
	rtrn = NULL;
	while (my_list)
	{
		last = malloc(sizeof(t_list));
		if (!last)
		{
			ft_lstclear(&rtrn, del);
			return (NULL);
		}
		last->content = f(my_list->content);
		last->next = NULL;
		ft_lstadd_back(&rtrn, last);
		my_list = my_list->next;
	}
	return (rtrn);
}
