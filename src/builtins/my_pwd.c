/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:54:03 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/28 18:55:38 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_pwd_error(t_env *env)
{
	char	*env_pwd;

	if (errno == ENOENT)
	{
		env_pwd = get_env_value("PWD", env);
		if (env_pwd)
		{
			printf("%s\n", env_pwd);
			return (0);
		}
	}
	perror("pwd");
	return (ERROR);
}

int	my_pwd(t_cmd_ex *data)
{
	char	pwd[PATH_MAX];

	if (data->args && data->args[1])
	{
		printf("pwd: too many arguments\n");
		return (ERROR);
	}
	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
		return (0);
	}
	return (handle_pwd_error(data->mini->env_head));
}
