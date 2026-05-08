/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:52 by bcanals-          #+#    #+#             */
/*   Updated: 2026/05/08 13:45:08 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// quick line to close 2 fds and print the errors if there are any

void	my_close(int *fd1, int *fd2, char *msg)
{
	if (fd1 && *fd1 > 2)
	{
		if (close(*fd1) == -1)
			perror(msg);
		*fd1 = -1;
	}
	if (fd2 && *fd2 > 2)
	{
		if (close(*fd2) == -1)
			perror(msg);
		*fd2 = -1;
	}
}

// Manages the dup2 with its error handlings

int	redirect(t_mini *mini)
{
	if ((dup2(mini->ex->fds[OLD_FDS][P_READ], STDIN_FILENO) == -1) ||
		(dup2(mini->ex->fds[NEW_FDS][P_WRITE], STDOUT_FILENO) == -1))
		return (0);
	return (1);
}

// Util function to set the fds for parent process managing a builtin

void	set_std_fds(t_mini *mini)
{
	mini->ex->fds[OLD_FDS][P_READ] = STDIN_FILENO;
	mini->ex->fds[NEW_FDS][P_WRITE] = STDOUT_FILENO;
}

// Util function to restore stdin and stdout for parent process w builtin
void	repair_std_fds(t_mini *mini)
{
	dup2(mini->saved_stdin, STDIN_FILENO);
	dup2(mini->saved_stdout, STDOUT_FILENO);
}

// Waits for all the child pid_t processes

/* ... existing code ... */

void	wait_childs(t_mini *mini, pid_t *childs)
{
	int	status;

	while (childs && *childs)
	{
		if (waitpid(*childs++, &status, 0) == -1)
			perror("waitpid");
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			mini->exit_status = 128 + WTERMSIG(status);
			if (mini->exit_status == 130)
				write(1, "\n", 1);
			else if (mini->exit_status == 131)
				write(1, "Quit (core dumped)\n", 19);
		}
	}
}
