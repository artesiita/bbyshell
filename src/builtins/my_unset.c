/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:02 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/08 19:00:01 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_env_variable(t_mini *mini, t_env *head, char *key)
{
	int		key_len;
	t_env	*tmp;
	t_env	*prev;

	key_len = ft_strlen(key);
	prev = head;
	if (ft_strncmp(head->key, key, key_len + 1) == 0
		&& ((int)ft_strlen(head->key) == key_len))
	{
		mini->env_head = head->next;
	}
	while (head)
	{
		if (ft_strncmp(head->key, key, key_len + 1) == 0
			&& ((int)ft_strlen(head->key) == key_len))
		{
			tmp = head;
			if (head->next)
				prev->next = tmp->next;
			else
			{
				prev->next = NULL;
				mini->env_cur = prev;
			}
			head = head->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
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
