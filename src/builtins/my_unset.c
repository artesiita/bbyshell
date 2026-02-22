/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:02 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/22 13:26:16 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_unset(t_cmd_ex *data)
{
	printf("Aquí executem el builtin de my_unset, he rebut %s\n", data->args[0]);
	return (0);
}
