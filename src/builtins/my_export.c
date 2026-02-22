/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:54:35 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/22 13:25:51 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_export(t_cmd_ex *data)
{
	printf("Aquí executem el builtin de my_export, he rebut %s\n", data->args[0]);
	return (0);
}
