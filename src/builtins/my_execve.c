/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:10:57 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/21 23:15:57 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static 	int (*get_builtin_ft(t_cmd_ex *data))(t_cmd_ex *)
{
	printf("comprovant el builtin: %s\n", data->path);
	if (ft_strcmp(data->path, "echo"))
		return (&my_echo);
	else if (ft_strcmp(data->path, "cd"))
		return (my_cd);
	else if (ft_strcmp(data->path, "pwd"))
		 return (&my_pwd);
	else if (ft_strcmp(data->path, "export"))
		 return (&my_export);
	else if (ft_strcmp(data->path, "unset"))
		 return (&my_unset);
	else if (ft_strcmp(data->path, "env"))
		 return (&my_env);
	else if (ft_strcmp(data->path, "exit"))
		 return (&my_exit);
	else
		 return (NULL);
}

int	my_execve(t_cmd_ex *data, t_executor *ex)
{
	int (*builtin_ft)(t_cmd_ex *);

	builtin_ft = get_builtin_ft(data);
	if (builtin_ft)
		return (builtin_ft(data));
	else
		return (execve(data->path, data->args, ex->env));
}
