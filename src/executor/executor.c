/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:25:50 by becanals          #+#    #+#             */
/*   Updated: 2026/04/11 17:40:49 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		do_childs(t_mini *mini);
static pid_t	my_fork(t_mini *mini);
static void		set_cmd_redirs(t_mini *mini);
static void		my_pipe(t_mini *mini);

/* 
	main functin of the executor section of the Minishell.
	Receives a full mini with a parsed input, executes the correct commands,
	handles errors and its input, sets the errno and returns the control.
 */

void	ft_executor(t_mini *mini)
{
	signals_nonintmode();
	mini->ex->cur_cmd = mini->cmds;
	if (ft_lstcount(mini->cmds) != 1 || !get_builtin_ft(mini))
	{
		mini->ex->childs = ft_calloc(ft_lstcount(mini->cmds) + 1, sizeof(pid_t));
		if (!mini->ex->childs)
			exit(EXIT_FAILURE); // faltarà gestionar l'error del malloc
		do_childs(mini);
		if (mini->ex->childs && *(mini->ex->childs))
			wait_childs(mini->ex->childs);
		free(mini->ex->childs);
		mini->ex->childs = NULL;
	}
	else
	{
		mini->ex->fds[OLD_FDS][P_READ] = STDIN_FILENO;
		mini->ex->fds[NEW_FDS][P_WRITE] = STDOUT_FILENO;
		set_cmd_redirs(mini);
		if(!redirect(mini))
		{
			//NO ESTIC SEGUR QUE AIXÒ TINGUI SENTIT AQUÍ
			//Gestionar l'error de dup2 (clean i exit) (no feia close)
		}
		if (my_execve(mini) == -1)
		{
			free_everything(mini);
			exit(127);
		}
	}
	ft_postex_clean(mini);
	// un free especial per l'struct de executor.
}

/*
   Handles the iteration of creating a child process for each cmd
*/

static void	do_childs(t_mini *mini)
{
	int	i;

	i = 0;
	mini->ex->fds[OLD_FDS][P_READ] = 1;
	mini->ex->fds[OLD_FDS][P_WRITE] = -1;
	while (mini->ex->cur_cmd)
	{
		//printf("flag 1, fd == %i\n", mini->ex->fds[OLD_FDS][P_READ]);
		my_pipe(mini);
		//printf("flag 2, fd == %i\n", mini->ex->fds[OLD_FDS][P_READ]);
		mini->ex->childs[i] = my_fork(mini);
		if (mini->ex->childs[i++] == -1)
		{
			// funció de neteja que inclou close
			// gestió de l'error
		}
		my_close(&(mini->ex->fds[OLD_FDS][P_READ]),
			&(mini->ex->fds[OLD_FDS][P_WRITE]),
			"close in main proc after forking");
		mini->ex->fds[OLD_FDS][P_READ] = mini->ex->fds[NEW_FDS][P_READ];
		mini->ex->fds[OLD_FDS][P_WRITE] = mini->ex->fds[NEW_FDS][P_WRITE];
		mini->ex->cur_cmd = mini->ex->cur_cmd->next;
	}
	return ;
}

/*
	Handles the forking process and manages errors
*/

static pid_t	my_fork(t_mini *mini)
{
	pid_t	my_id;

	my_id = fork();
	if (my_id == -1)
		return (my_id);
	else if (my_id == 0)
	{
		printf("procés %i = fill ex\n", getpid()); 
		my_close(&(mini->ex->fds[OLD_FDS][P_WRITE]),
			&(mini->ex->fds[NEW_FDS][P_READ]), "close in child pre execve");
		set_cmd_redirs(mini);
		if(!redirect(mini))
		{
			// Gestionar l'error de dup2 (clean i exit) (no feia close)
		}
		dump_heredoc(mini);
		//printf("pare ha tornat post dump_heredoc\n");
		if (my_execve(mini) == -1)
		{
			free_everything(mini);
			exit(127);
		}
		my_close(&(mini->ex->fds[OLD_FDS][P_READ]), &(mini->ex->fds[NEW_FDS][P_WRITE]),
			 "close in child afer execve");
		exit(EXIT_SUCCESS);
	}
	return (my_id);
}

/*
	Review the cmd redirection instructions and updates the fds accordingly
*/

static void	set_cmd_redirs(t_mini *mini)
{
	t_redir	*redir;

	redir = mini->cmds->redirs;
	while (redir)
	{
		if (redir->type == R_IN)
			ft_redir_in(mini, redir);
		else if (redir->type == R_OUT)
			ft_redir_out(mini, redir);
		else if (redir->type == R_APPEND)
			ft_redir_append(mini, redir);
		else if (redir->type == R_HEREDOC)
			ft_redir_heredoc(mini, redir);
		redir = redir->next;
	}
}

/*
   Updates fds depending on if we are in the last cmd (stdout & null) or else (pipe)
*/

static void	my_pipe(t_mini *mini)
{
	if (mini->ex->cur_cmd->next)
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
