/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 04:17:34 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/22 17:12:32 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_lstmap(void *lst, void (*f)(void *), void (*del)(void *),
				int struct_size)
{
	void	*rtrn;
	void	*last;
	void	*my_list;

	my_list = lst;
	if (!my_list || !f || !del)
		return (NULL);
	rtrn = NULL;
	while (my_list)
	{
		last = malloc(struct_size);
		if (!last)
		{
			ft_lstclear(&rtrn, del);
			return (NULL);
		}
		f(my_list);
		*(void **)last = NULL;
		ft_lstadd_back(&rtrn, last);
		my_list = *(void **)my_list;
	}
	return (rtrn);
}
