/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:26:13 by lartes-s          #+#    #+#             */
/*   Updated: 2026/02/13 17:28:09 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	commands_counter(t_token *head)
{
	int	count;

	count = 0;
	while (head && head->type != T_PIPE)
	{
		if (head->type == T_WORD)
		{
			count++;
			head = head->next;
		}
		else
		{
			head = head->next;
			if (head)
				head = head->next;
		}
	}
	return (count);
}

void	add_command_node(t_cmds **head, t_cmds *new_node)
{
	t_cmds	*tmp;

	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
