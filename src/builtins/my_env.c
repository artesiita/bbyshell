/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:23 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/22 17:09:19 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_env(t_cmd_ex *data)
{
	t_env	*current;

	if (!data || !data->mini || !data->mini->env)
		return (1);
	if (data->args && data->args[0] && data->args[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(data->args[1], STDERR_FILENO);
		ft_putstr_fd("command not found", STDERR_FILENO);
		data->mini->exit_status = 127;
		return (127);
	}
	current = data->mini->env;
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
