/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:44 by bizcru            #+#    #+#             */
/*   Updated: 2026/04/11 16:19:55 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

long	handle_exit_argument(char *str)
{
	if (!is_valid_long(str))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
	}
	return (ft_atol(str));
}

int	my_exit(t_mini *mini)
{
	long	exit_status;
	char	**args;

	args = mini->ex->cur_cmd->args;
	printf("exit\n");
	if (args[1] && ft_isdigit_str(args[1]) && args[2])
		return (ft_putstr_fd("exit: too many arguments\n", 2), ERROR);
	if (args[1])
		exit_status = handle_exit_argument(args[1]);
	else
		exit_status = mini->exit_status;
	free_everything(mini);
	exit(exit_status);
	return (ERROR);
}
