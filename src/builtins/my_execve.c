/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:10:57 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/07 18:36:10 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Helper function for get_path to manage the error handling.

static char	*set_error(int *my_errno, char *msg, char **msg_add)
{
	*my_errno = errno;
	*msg_add = msg;
	return (NULL);
}

// Gets the path (if valid one) of the cmd of the child.
// Manages errors to allow load_data print the correct error info.

static char	*get_path(char *cmd, t_env *env, int *my_errno, char **msg_add)
{
	int		i;
	char	**paths;
	char	*this_path;
	t_env	*my_env;

	my_env = env;
	while (my_env && !(ft_streq(my_env->key, "PATH")))
		my_env = my_env->next;
	if (my_env)
		paths = ft_split(my_env->value, ':');
	if (!my_env || !paths)
		return (set_error(my_errno, "env PATH not found\n", msg_add));
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
	return (set_error(my_errno, "command not found", msg_add));
}

static int (*get_builtin_ft(t_mini *mini))(t_mini *)
{
	char	*cmd;

	cmd = mini->ex->cur_cmd->args[0];
	if (ft_streq(cmd, "echo"))
		return (&my_echo);
	// else if (ft_streq(cmd, "cd"))
	//	return (my_cd);
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
	int		my_errno;
	char	*msg;
	char	*path;

	builtin_ft = get_builtin_ft(mini);
	if (builtin_ft)
		return (builtin_ft(mini));
	path = get_path(mini->ex->cur_cmd->args[0], mini->env_head, &my_errno,
			&msg);
	if (!path)
	{
		// Fer free i gestionar el tema dels error message
	}
	return (execve(path, mini->ex->cur_cmd->args, env_compile(mini->env_head)));
}
