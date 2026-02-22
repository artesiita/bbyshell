/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:23 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/22 16:48:30 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_env(t_cmd_ex *data)
{
	t_env	*current;

	write(1, "adeu env2\n", 10);
	if (!data || !data->mini || !data->mini->env)
	{
		write(1, "error 1\n", 8);
		return (1);
	}
	if (data->args && data->args[0] && data->args[1])
	{
		write(1, "error 2\n", 8);
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(data->args[1], STDERR_FILENO);
		ft_putstr_fd("command not found", STDERR_FILENO);
		data->mini->exit_status = 127;
		return (127);
	}
	write(1, "current = data:\n", 17);
	current = data->mini->env;
	while (current)
	{
		if (current->key && current->value)
		{
			printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
	return (0);
}
