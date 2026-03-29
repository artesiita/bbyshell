/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:32:20 by lartes-s          #+#    #+#             */
/*   Updated: 2026/03/29 17:08:31 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(char *key, t_env *env)
{
	int		key_len;
	char	*value;
	t_env	*cur;

	cur = env;
	key_len = ft_strlen(key);
	while (cur)
	{
		if (ft_strncmp(cur->key, key, key_len + 1) == 0
			&& ((int)ft_strlen(cur->key) == key_len))
			return (value = cur->value);
		cur = cur->next;
	}
	return (NULL);
}

void	update_env_value(t_env *env, char *key, char *new_value)
{
	int		key_len;
	t_env	*cur;

	if (!key || !env)
		return ;
	cur = env;
	key_len = ft_strlen(key);
	while (cur)
	{
		if (ft_strncmp(cur->key, key, key_len + 1) == 0
			&& ((int)ft_strlen(cur->key) == key_len))
		{
			free(cur->value);
			if (new_value)
				cur->value = ft_strdup(new_value);
			else
				cur->value = ft_strdup("");
			return ;
		}
		cur = cur->next;
	}
}

t_env	*create_node(t_mini *mini, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		fatal_error(mini, "bbyshell: malloc: cannot alocate memory\n", 1);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
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
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
