/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:25:50 by becanals          #+#    #+#             */
/*   Updated: 2026/04/18 16:29:54 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		do_childs(t_mini *mini);
static pid_t	my_fork(t_mini *mini);
static void		set_cmd_redirs(t_mini *mini);
static int		my_pipe(t_mini *mini);

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
			perror("malloc");
		else
		{
			do_childs(mini);
			wait_childs(mini->ex->childs);
			free(mini->ex->childs);
			mini->ex->childs = NULL;
		}
	}
	else
	{
		mini->ex->fds[OLD_FDS][P_READ] = STDIN_FILENO;
		mini->ex->fds[NEW_FDS][P_WRITE] = STDOUT_FILENO;
		set_cmd_redirs(mini);
		if(redirect(mini))
			mini->exit_status = my_execve(mini);
	}
	ft_postex_clean(mini);
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
		if (!my_pipe(mini))
		{
			// aquí un printerror;
			return (ft_postex_clean(mini));
		}
		mini->ex->childs[i] = my_fork(mini);
		if (mini->ex->childs[i++] == -1)
		{
			// aquí un printerror;
			return (ft_postex_clean(mini));
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
		my_close(&(mini->ex->fds[OLD_FDS][P_WRITE]),
			&(mini->ex->fds[NEW_FDS][P_READ]), "close in child pre execve");
		set_cmd_redirs(mini);
		if(!redirect(mini))
			ex_exit(mini, errno);
		dump_heredoc(mini);
		ex_exit(mini, my_execve(mini));
	}
	return (my_id);
}

/*
	Review the cmd redirection instructions and updates the fds accordingly
*/

static void	set_cmd_redirs(t_mini *mini)
{
	t_redir	*redir;

	redir = mini->ex->cur_cmd->redirs;
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

static int	my_pipe(t_mini *mini)
{
	if (mini->ex->cur_cmd->next)
	{
		if (pipe(mini->ex->fds[NEW_FDS]) == -1)
			return (0);
	}
	else
	{
		(mini->ex->fds)[NEW_FDS][P_READ] = -1;
		(mini->ex->fds)[NEW_FDS][P_WRITE] = 1;
	}
	return (1);
}
