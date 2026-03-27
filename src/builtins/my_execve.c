/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:10:57 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/27 19:33:58 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*Gets the path (if valid one) of the cmd of the child.
Manages errors to allow load_data print the correct error info.*/

static char	*get_path(char *cmd, t_env *env)
{
	int		i;
	char	**paths;
	char	*this_path;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (cmd);
	if (ft_strchr(cmd, '/'))
		return (NULL);
	paths = ft_split(get_env_value("PATH", env), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		this_path = ft_strjoins(paths[i], "/", cmd);
		if (access(this_path, X_OK) == 0)
		{
			ft_free_array(paths);
			return (this_path);
		}
		free(this_path);
	}
	ft_free_array(paths);
	return (NULL);
}

int (*get_builtin_ft(t_mini *mini))(t_mini *mini)
{
	char	*cmd;

	cmd = mini->ex->cur_cmd->args[0];
	if (ft_streq(cmd, "echo"))
		return (&my_echo);
	else if (ft_streq(cmd, "cd"))
		return (my_cd);
	else if (ft_streq(cmd, "pwd"))
		return (&my_pwd);
	else if (ft_streq(cmd, "export"))
		return (&my_export);
	else if (ft_streq(cmd, "unset"))
		return (&my_unset);
	else if (ft_streq(cmd, "env"))
		return (&my_env);
	else if (ft_streq(cmd, "exit"))
		return (&my_exit);
	else
		return (NULL);
}

static char	**env_compile(t_env *env_list)
{
	int		i;
	t_env	*counter;
	char	**env;
	char	*temp;

	i = 0;
	counter = env_list;
	while (counter)
	{
		i++;
		counter = counter->next;
	}
	env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env_list)
	{
		temp = ft_strjoin(env_list->key, "=");
		env[i++] = ft_strjoin(temp, env_list->value);
		free(temp);
		env_list = env_list->next;
	}
	return (env);
}

int	my_execve(t_mini *mini)
{
	int		(*builtin_ft)(t_mini *);
	char	*path;

	builtin_ft = get_builtin_ft(mini);
	if (builtin_ft)
		return (builtin_ft(mini));
	path = get_path(mini->ex->cur_cmd->args[0], mini->env_head);
	if (!path)
	{
		perror(mini->ex->cur_cmd->args[0]);
		return (0);
	}
	return (execve(path, mini->ex->cur_cmd->args, env_compile(mini->env_head)));
}
