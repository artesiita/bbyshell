/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:23 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/22 13:07:31 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_env(t_cmd_ex *data)
{
	t_env	*current;

	current = data->mini->env;
	if (!data->mini->env || !data->mini->env->key || !data->mini->env->value)
		return (1);
	if (data->args[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(data->args[1], STDERR_FILENO);
		ft_putstr_fd("command not found", STDERR_FILENO);
	}
	while (current)
	{
		if (current->value)
		{
			printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
	return (0);
}
