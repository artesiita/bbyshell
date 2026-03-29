/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:33:14 by lartes-s          #+#    #+#             */
/*   Updated: 2026/03/29 17:00:58 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*create_env_node(t_mini *mini, char *content)
{
	t_env	*new;
	char	*limit;

	if (!content)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		fatal_error(mini, "bbyshell: malloc: cannot allocate memory\n", 1);
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

int	append_env_node(t_mini *mini, t_env **head, t_env **cur, char *content)
{
	t_env	*node;

	node = create_env_node(mini, content);
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
	int	i;

	mini->env_head = NULL;
	mini->env_cur = NULL;
	i = 0;
	if (env && *env)
	{
		while (env[i])
		{
			if (!append_env_node(mini, &mini->env_head, &mini->env_cur, env[i]))
				return (free_env_list(mini->env_head), 0);
			i++;
		}
	}
	return (1);
}
