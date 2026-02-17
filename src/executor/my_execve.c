/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:10:57 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/15 12:25:45 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	get_builtin_ft(t_cmd_ex *data, int (*funct)(t_cmd_ex *))
{
	if (ft_strcmp(data->path, "env")
		funct = &my_env
}

int	my_execve(t_cmd_ex *data)
{
	int (*bulitin_ft)(t_cmd_ex *);

	get_builtin_ft(data, &builtin_ft);
	if (builtin_ft)
		return (builtin_ft(data));
	else
		return (execve(data->path, data->args, ex->env));
}
