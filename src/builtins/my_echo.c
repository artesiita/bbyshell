/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:50:53 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/22 13:25:24 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_echo(t_cmd_ex *data)
{
	printf("Aquí executem el builtin de my_echo, he rebut %s\n", data->args[0]);
	return (0);
}
