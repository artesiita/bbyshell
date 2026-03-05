/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:53:23 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/28 19:47:10 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	go_home(t_cmd_ex *data, char *old_path)
{
	char	*path;

	path = get_env_value("HOME", data->mini->env_head);
	if (!path)
	{
		perror("cd: HOME not set");
		return (ERROR);
	}
	if (chdir(path) == -1)
}


int	my_cd(t_cmd_ex *data)
{
	char	*path;
	char	old_path[PATH_MAX];

	if (data->args[1] && data->args[2])
	{
		printf("bbyshell: cd: too many arguments\n");
		return (ERROR);
	}
	if (!getcwd(old_path, sizeof(old_path)))
		old_path = get_env_value("PWD", data->mini->env_head);
	if (!data->args[1])
		return (go_home(data, old_path));
	return (0);
}
