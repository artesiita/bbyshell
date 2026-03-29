/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:07:50 by lartes-s          #+#    #+#             */
/*   Updated: 2026/03/29 17:08:27 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	swap_env_nodes(t_env *cur, char *tmp_key, char *tmp_val, int *swapped)
{
	if (ft_strcmp(cur->key, cur->next->key) > 0)
	{
		tmp_key = cur->key;
		cur->key = cur->next->key;
		cur->next->key = tmp_key;
		tmp_val = cur->value;
		cur->value = cur->next->value;
		cur->next->value = tmp_val;
		*swapped = 1;
	}
}

void	sort_env(t_env *head)
{
	t_env	*cur;
	char	*tmp_key;
	char	*tmp_val;
	int		swapped;

	if (!head)
		return ;
	swapped = 1;
	tmp_key = NULL;
	tmp_val = NULL;
	while (swapped)
	{
		swapped = 0;
		cur = head;
		while (cur && cur->next)
		{
			if (cur->key && cur->next->key)
				swap_env_nodes(cur, tmp_key, tmp_val, &swapped);
			cur = cur->next;
		}
	}
}

int	check_env_variable(t_env *head, char *key)
{
	int		key_len;
	t_env	*cur;

	cur = head;
	key_len = ft_strlen(key);
	while (cur)
	{
		if (ft_strncmp(cur->key, key, key_len + 1) == 0
			&& ((int)ft_strlen(cur->key) == key_len))
			return (1);
		cur = cur->next;
	}
	return (0);
}

t_env	*env_cpy(t_mini *mini, t_env *head)
{
	t_env	*new_list;
	t_env	*current;
	t_env	*last;
	t_env	*new_node;

	if (!head)
		return (NULL);
	new_list = NULL;
	current = head;
	while (current)
	{
		new_node = create_node(mini, current->key, current->value);
		if (!new_node)
			return (NULL);
		if (!new_list)
			new_list = new_node;
		else
			last->next = new_node;
		last = new_node;
		current = current->next;
	}
	return (new_list);
}
