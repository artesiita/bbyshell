/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:44 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/22 13:25:40 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_exit(t_cmd_ex *data)
{
	data->mini->exit_status = -1;
	exit(EXIT_SUCCESS);
	printf("Aquí executem el builtin de my_exit, he rebut %s\n", data->args[0]);
	return (0);
}
