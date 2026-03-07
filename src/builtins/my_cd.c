/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:53:23 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/07 16:18:58 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_directory(t_cmd_ex *data, char *old_path, char **args)
{
	char	*cur_path;
	char	*path;

	if (args[1][0] == '-' && args[1][1] == '\0')
	{
		path = get_env_value("OLDPWD", data->mini->env_head);
		if (!path)
		{
			printf("cd: OLDPWD not set");
			return (ERROR);
		}
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			perror("cd: ");
			return (ERROR);
		}
		cur_path = getcwd(NULL, 0);
		update_env_value(data->mini->env_head, "PWD", cur_path);
		update_env_value(data->mini->env_head, "OLDPWD", old_path);
		free(cur_path);
	}
}

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
	{
		perror("cd: ");
		return (ERROR);
	}
	update_env_value(data->mini->env_head, "OLDPWD", old_path);
	update_env_value(data->mini->env_head, "PWD", path);
	return (0);
}

int	my_cd(t_cmd_ex *data)
{
	char	*path;
	char	*oldpwd;

	if (data->args[1] && data->args[2])
	{
		printf("bbyshell: cd: too many arguments\n");
		return (ERROR);
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup(get_env_value("PWD", data->mini->env_head));
	if (!data->args[1] || (data->args[1][0] == '-' && data->args[1][1] == '-'
			&& data->args[1][2] == '\0'))
		go_home(data, oldpwd);
	else
		change_directory(data, oldpwd, data->args);
	free(oldpwd);
	return (0);
}
