/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:51:15 by bcanals-          #+#    #+#             */
/*   Updated: 2024/12/14 16:55:37 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Closes open fds and exits

void	close_exit(int *fds, int my_errno, char *msg)
{
	my_close(fds[0], fds[1], "close in main");
	handle_err(my_errno, msg);
}

// Closes open fds and also frees the pid_t array childs

void	free_close_exit(int *fds1, int *fds2, pid_t *childs, char *msg)
{
	int	my_errno;

	my_errno = errno;
	my_close(fds1[0], fds1[1], "close in main");
	if (fds2)
		my_close(fds2[0], fds2[1], "close in main");
	free(childs);
	handle_err(my_errno, msg);
}

// Waits for all the child pid_t processes

void	wait_childs(pid_t *childs)
{
	while (*childs != 0)
		if (waitpid(*childs++, NULL, 0) == -1)
			perror("waitpid");
}
