/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:23 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/07 18:09:11 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_env(t_mini *mini)
{
	t_env	*current;
	char	**ag;

	ag = mini->ex->cur_cmd->args;
	if (!mini || !mini->env_head)
		return (1);
	if (ag && ag[0] && ag[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(ag[1], STDERR_FILENO);
		ft_putstr_fd(" command not found\n", STDERR_FILENO);
		mini->exit_status = 127;
		return (127);
	}
	current = mini->env_head;
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
