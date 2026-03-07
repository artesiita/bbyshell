/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:25:50 by becanals          #+#    #+#             */
/*   Updated: 2026/03/07 16:49:01 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		do_childs(t_mini *mini);
static pid_t	my_fork(t_mini *mini);
static void		set_cmd_redirs(t_mini *mini);
static void		my_pipe(t_mini *mini);
static int		count_cmds(t_cmds *cmds);
static void		wait_childs(pid_t *childs);

// main functin of the executor section of the Minishell.
// Receives a full mini with a parsed input, executes the correct commands,
//   handles errors and its input, sets the errno and returns the control.

void	ft_executor(t_mini *mini)
{
	mini->ex = ft_calloc(1, sizeof(t_executor));
	if (!mini->ex) // faltarà gestionar l'eror d'això
		exit(EXIT_FAILURE);
	mini->ex->childs = ft_calloc(count_cmds(mini->cmds), sizeof(pid_t));
	if (!mini->ex->childs)
		exit(EXIT_FAILURE); // faltarà gestionar l'error del malloc
	mini->ex->fds[OLD_FDS][P_READ] = 1;
	mini->ex->fds[OLD_FDS][P_WRITE] = -1;
	do_childs(mini);
	if (mini->ex->childs && *(mini->ex->childs))
		wait_childs(mini->ex->childs);
	//Aqui falta gestionar millor la neteja de memoria, basicament caldra fer
		//un free especial per l'struct de executor.
}

// Handles the iteration of creating a child process for each cmd

static void	do_childs(t_mini *mini)
{
	int		i;

	i = 0;
	mini->ex->cur_cmd = mini->cmds;
	while (mini->ex->cur_cmd)
	{
		my_pipe(mini);
		mini->ex->childs[i] = my_fork(mini);
		if (mini->ex->childs[i++] == -1)
		{
			//funció de neteja que inclou close
			//gestió de l'error
		}
		my_close(mini->ex->fds[OLD_FDS][P_READ], mini->ex->fds[OLD_FDS][P_WRITE], 
			"close in main proc after forking");
		mini->ex->fds[OLD_FDS][P_READ] = mini->ex->fds[NEW_FDS][P_READ];
		mini->ex->fds[OLD_FDS][P_WRITE] = mini->ex->fds[NEW_FDS][P_WRITE];
		mini->ex->cur_cmd = mini->ex->cur_cmd->next;
	}
	return ;
}

// Handles the forking process and manages errors

static pid_t	my_fork(t_mini *mini)
{
	pid_t		my_id;

	my_id = fork();
	if (my_id == -1)
		return (my_id);
	else if (my_id == 0)
	{
		my_close(mini->ex->fds[OLD_FDS][P_WRITE], mini->ex->fds[NEW_FDS][P_READ],
			"close in child pre execve");
		set_cmd_redirs(mini);
		if(!redirect(mini))
		{
			//Gestionar l'error de dup2 (clean i exit) (no feia close)
		}
		if (my_execve(mini) == -1)
		{
			//Fer clean i exit
		}
		my_close(mini->ex->fds[OLD_FDS][P_READ], mini->ex->fds[NEW_FDS][P_WRITE],
			 "close in child afer execve");
		exit(EXIT_SUCCESS);
	}
	return (my_id);
}

// Review the cmd redirection instructions and updates the fds accordingly

static void	set_cmd_redirs(t_mini *mini)
{
	t_redir	*redir;

	redir = mini->cmds->redirs;
	while (redir)
	{
		if (redir->type == R_IN)
		{
			close(mini->ex->fds[NEW_FDS][P_READ]);
			mini->ex->fds[NEW_FDS][P_READ] = open(redir->target, O_RDONLY);
		}
		else if (redir->type == R_OUT)
		{
			close(mini->ex->fds[NEW_FDS][P_WRITE]);
			mini->ex->fds[NEW_FDS][P_WRITE] = open(redir->target, O_RDONLY);
		}
		redir = redir->next;
	}
}

// Updates fds depending on if we are in the last cmd (stdout & null) or else (pipe)

static void	my_pipe(t_mini *mini)
{
	if (mini->cmds->next)
	{
		if (pipe(mini->ex->fds[NEW_FDS]) == -1)
		{
			mini->ex->fds[NEW_FDS][P_READ] = -1;
			mini->ex->fds[NEW_FDS][P_WRITE] = -1;
			// funció clean (que inclogui close!)
			// gestió de l'errnum
		}
	}
	else
	{
		(mini->ex->fds)[NEW_FDS][P_READ] = -1;
		(mini->ex->fds)[NEW_FDS][P_WRITE] = 1;
	}
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

// Waits for all the child pid_t processes

static void	wait_childs(pid_t *childs)
{
	while (childs && *childs != 0)
		if (waitpid(*childs++, NULL, 0) == -1)
			perror("waitpid");
}
