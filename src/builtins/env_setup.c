/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:33:14 by lartes-s          #+#    #+#             */
/*   Updated: 2026/02/27 18:20:03 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*create_env_node(char *content)
{
	t_env	*new;
	char	*limit;

	if (!content)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	limit = (char *)ft_strchr(content, '=');
	if (limit)
	{
		new->key = ft_substr(content, 0, limit - content);
		new->value = ft_strdup(limit + 1);
	}
	else
	{
		new->key = ft_strdup(content);
		new->value = NULL;
	}
	new->next = NULL;
	return (new);
}

int	append_env_node(t_env **head, t_env **cur, char *content)
{
	t_env	*node;

	node = create_env_node(content);
	if (!node)
		return (0);
	if (*head == NULL)
		*head = node;
	else
		(*cur)->next = node;
	*cur = node;
	return (1);
}

int	env_setup(t_mini *mini, char **env)
{
	t_env	*head;
	t_env	*cur;
	int		i;

	if (!env || !*env)
		return (0);
	head = NULL;
	cur = NULL;
	i = 0;
	if (env && *env)
	{
		while (env[i])
		{
			if (!append_env_node(&head, &cur, env[i]))
				return (free_env_list(head), 0);
			i++;
		}
	}
	else
	{
		if (!append_env_node(&head, &cur, ""))
			return (free_env_list(head), 0);
	}
	mini->env_head = head;
	mini->env_cur = cur;
	return (1);
}
