/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:32:20 by lartes-s          #+#    #+#             */
/*   Updated: 2026/02/22 19:36:59 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*create_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

/*
t_env	*create_env_node(char *content)
{
	t_env   *new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
}*/