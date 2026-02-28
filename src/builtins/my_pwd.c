/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:54:03 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/28 18:24:43 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(char *key, t_env *env)
{
	int		key_len;
	char	*value;
	t_env	*cur;

	cur = env;
	key_len = ft_strlen(key);
	while (cur)
	{
		if (strcmp(cur->key, key) && ((int)ft_strlen(cur->key) == key_len))
			return (value = cur->value);
		cur = cur->next;
	}
	return (NULL);
}

static int	handle_pwd_error(t_env *env)
{
	char	*env_pwd;

	if (errno == ENOENT)
	{
		env_pwd = get_env_value("PWD", env);
		if (env_pwd)
		{
			printf("%s\n", env_pwd);
			return (1);
		}
	}
	perror("pwd");
	return (0);
}

int	my_pwd(t_cmd_ex *data)
{
	char	pwd[PATH_MAX];

	if (data->args && data->args[1])
	{
		printf("pwd: too many arguments\n");
		return (0);
	}
	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
		return (1);
	}
	return (handle_pwd_error(data->mini->env_head));
}
