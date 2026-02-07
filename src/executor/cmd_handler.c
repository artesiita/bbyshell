/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becanals <becanals@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:25:50 by becanals          #+#    #+#             */
/*   Updated: 2026/02/07 17:22:09 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Review the cmd redirection instructions and updates the fds accordingly

static void	set_cmd_redirs(t_cmds *cmd, int **fds)
{
	
}

// Handles the forking process and manages errors

pid_t	my_fork(t_cmds *cmd, char **env, int **fds, pid_t *childs)
{
	pid_t	my_id;
	t_cmd_ex	*data;

	my_id = fork();
	if (my_id == -1)
		return (my_id);
	else if (my_id == 0)
	{
		free(childs);
		my_close(fds[1][1], fds[0][0], "close in child pre execve");
		//set_cmd_redirs(cmd, fds) 
		data = load_data(cmd->args, env, fds[1][0], fds[0][1]);
		//redirect(data);
		if (execve(data->path, data->args, env) == -1)
			clean_exit(data, errno, "execve");
		my_close(data->fd_in, data->fd_out, "close in child afer execve");
		//printf("exit amb exit: %i", getpid());
		exit(EXIT_SUCCESS);
	}
	return (my_id);
}

// Aquesta funcio clarament no va aqui, hi esta temporalment mentre no existeix una
// funcio recompte generica

static int	count_cmds(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

// Updates fds depending on if we are in the last cmd (stdout & null) or else (pipe)

static void	update_oldfds()
{
	
}

// Handles the iteration of creating a child process for each cmd

pid_t	*do_childs(int **fds, t_mini *mini, char **env)
{
	int		i;

	//if (!childs)
	//	close_exit(fds[1], errno, "ft_calloc");
	i = 0;
	while (ex->cmds)
	{
		if (ex->cmds->next)
			if (pipe(fds[0]) == -1)
				free_close_exit(fds[1], NULL, childs, "pipe");
		else
			fds[0][];
		childs[i] = my_fork(ex->cmds, env, fds, childs);
		if (childs[i++] == -1)
			free_close_exit(fds[1], fds[0], childs, "fork");
		my_close(fds[1][0], fds[1][1], "close in main proc after forking");
		fds[1][0] = fds[0][0];
		fds[1][1] = fds[0][1];
		ex->cmds = ex->cmds->next;
	}
	return (childs);
}

static char **env_compile(t_env *env_list)
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

void	cmd_handler(t_mini *mini)
{
	t_executor	*ex;

	ex = ft_calloc(1, sizeof(t_executor));
	if (!executor)
		exit(EXIT_FAILURE);
	ex->env = env_compile(mini->env);
	ex->cmds = mini->cmds;
	ex->childs = ft_calloc(count_cmds(ex->cmds), sizeof(pid_t));
	ex->fds[1][0] = 0;
	ex->fds[1][1] = 1;
	//ft_print_array(env_compile(mini->env));
	do_childs(fds, mini, env_compile(mini->env));
	//my_close(oldfds[0], oldfds[1], "olds");
	//my_close(newfds[0], newfds[1], "news");
	wait_childs(ex->childs);
	//Aqui falta gestionar millor la neteja de memoria, basicament caldra fer
		//un free especial per l'struct de executor.
	free(childs);
}
