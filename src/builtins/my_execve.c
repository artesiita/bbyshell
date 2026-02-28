/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:10:57 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/28 18:46:38 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int (*get_builtin_ft(t_cmd_ex *data))(t_cmd_ex *)
{
	char	*cmd;

	cmd = data->args[0];
	printf("comprovant el builtin: %s\n", cmd);
	if (!ft_strcmp(cmd, "echo"))
		return (&my_echo);
	else if (!ft_strcmp(cmd, "cd"))
		return (my_cd);
	else if (!ft_strcmp(cmd, "pwd"))
		return (&my_pwd);
	else if (!ft_strcmp(cmd, "export"))
		return (&my_export);
	else if (!ft_strcmp(cmd, "unset"))
		return (&my_unset);
	else if (!ft_strcmp(cmd, "env"))
		return (&my_env);
	else if (!ft_strcmp(cmd, "exit"))
		return (&my_exit);
	else
		return (NULL);
}

int	my_execve(t_cmd_ex *data, t_executor *ex)
{
	int		(*builtin_ft)(t_cmd_ex *);
	int		my_errno;
	char	*msg;

	builtin_ft = get_builtin_ft(data);
	if (builtin_ft)
		return (builtin_ft(data));
	data->path = get_path(data->args[0], ex->env, &my_errno, &msg);
	if (!data->path)
		clean_exit(data, my_errno, msg);
	return (execve(data->path, data->args, ex->env));
}
