/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:02 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/27 16:48:36 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	unlink_node(t_mini *mini, t_env *prev, t_env *head, t_env *tmp)
{
	if (head->next)
		prev->next = tmp->next;
	else
	{
		prev->next = NULL;
		mini->env_cur = prev;
	}
}

void	free_node(t_env *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	remove_env_variable(t_mini *mini, t_env *head, char *key)
{
	int		key_len;
	t_env	*tmp;
	t_env	*prev;

	key_len = ft_strlen(key);
	prev = head;
	if (ft_strncmp(head->key, key, key_len + 1) == 0
		&& ((int)ft_strlen(head->key) == key_len))
		mini->env_head = head->next;
	while (head)
	{
		if (ft_strncmp(head->key, key, key_len + 1) == 0
			&& ((int)ft_strlen(head->key) == key_len))
		{
			tmp = head;
			unlink_node(mini, prev, head, tmp);
			head = head->next;
			free_node(tmp);
		}
		else
		{
			prev = head;
			head = head->next;
		}
	}
}

int	my_unset(t_mini *mini)
{
	char	**ag;
	int		i;

	ag = mini->ex->cur_cmd->args;
	i = 1;
	while (ag[i])
	{
		if (check_env_variable(mini->env_head, ag[i]))
		{
			remove_env_variable(mini, mini->env_head, ag[i]);
			i++;
		}
		else
			i++;
	}
	return (0);
}
