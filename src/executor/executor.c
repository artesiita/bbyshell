/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becanals <becanals@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:25:50 by becanals          #+#    #+#             */
/*   Updated: 2026/02/22 18:59:31 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		do_childs(t_executor *ex);
static pid_t	my_fork(t_executor *ex);
static void		set_cmd_redirs(t_executor *ex);
static void		update_oldfds(t_executor *ex);

void	ft_executor(t_mini *mini)
{
	t_executor	*ex;

	ex = ft_calloc(1, sizeof(t_executor));
	if (!ex)
		exit(EXIT_FAILURE);
	//ex->env = env_compile(mini->env);
	ex->cmds = mini->cmds;
	ex->childs = ft_calloc(ft_lstcount(ex->cmds), sizeof(pid_t));
	ex->fds[1][0] = 1;
	ex->fds[1][1] = -1;
	ex->mini = mini;
	do_childs(ex);
	//my_close(oldfds[0], oldfds[1], "olds");
	//my_close(newfds[0], newfds[1], "news");
	if (ex->childs && *(ex->childs))
		wait_childs(ex->childs);
	//Aqui falta gestionar millor la neteja de memoria, basicament caldra fer
		//un free especial per l'struct de executor.
	free(ex->childs);
}

// Handles the iteration of creating a child process for each cmd

static void	do_childs(t_executor *ex)
{
	int		i;

	i = 0;
	while (ex->cmds)
	{
		update_oldfds(ex);
		ex->childs[i] = my_fork(ex);
		if (ex->childs[i++] == -1)
			free_close_exit(ex->fds[1], ex->fds[0], ex->childs, "fork");
		my_close(ex->fds[1][0], ex->fds[1][1], "close in main proc after forking");
		ex->fds[1][0] = ex->fds[0][0];
		ex->fds[1][1] = ex->fds[0][1];
		ex->cmds = ex->cmds->next;
	}
	return ;
}

// Handles the forking process and manages errors

static pid_t	my_fork(t_executor *ex)
{
	pid_t		my_id;
	t_cmd_ex	*data;

	my_id = fork();
	if (my_id == -1)
		return (my_id);
	else if (my_id == 0)
	{
		//maybe not necessary?
		free(ex->childs);
		my_close(ex->fds[1][1], ex->fds[0][0], "close in child pre execve");
		set_cmd_redirs(ex);
		data = load_data(ex, ex->fds[1][0], ex->fds[0][1]);
		redirect(data);
		if (my_execve(data, ex) == -1)
			clean_exit(data, errno, "execve");
		my_close(data->fd_in, data->fd_out, "close in child afer execve");
		//printf("exit amb exit: %i", getpid());
		exit(EXIT_SUCCESS);
	}
	return (my_id);
}

// Review the cmd redirection instructions and updates the fds accordingly

static void	set_cmd_redirs(t_executor *ex)
{
	t_redir	*redir;

	redir = ex->cmds->redirs;
	while (redir)
	{
		if (redir->type == R_IN)
		{
			close(ex->fds[0][0]);
			ex->fds[0][0] = open(redir->target, O_RDONLY);
		}
		else if (redir->type == R_OUT)
		{
			close(ex->fds[0][1]);
			ex->fds[0][1] = open(redir->target, O_RDONLY);
		}
		redir = redir->next;
	}
}

// Updates fds depending on if we are in the last cmd (stdout & null) or else (pipe)

static void	update_oldfds(t_executor *ex)
{
	if (ex->cmds->next)
	{
		if (pipe(ex->fds[0]) == -1)
			free_close_exit(ex->fds[1], NULL, ex->childs, "pipe");
	}
	else
	{
		(ex->fds)[0][0] = -1;
		(ex->fds)[0][1] = 1;
	}
}
