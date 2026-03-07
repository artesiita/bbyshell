/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:50:53 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/07 17:19:27 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_echo(t_mini *mini)
{
	printf("Aquí executem el builtin de my_echo, he rebut %s\n", mini->ex->cur_cmd->args[0]);
	return (0);
}
