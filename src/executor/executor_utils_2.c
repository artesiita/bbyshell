/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:32:22 by bcanals-          #+#    #+#             */
/*   Updated: 2026/02/22 18:23:46 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Loads the necessary data for the child process, also handles errors.

t_cmd_ex	*load_data(t_executor *ex, int fd_in, int fd_out)
{
	t_cmd_ex	*new;

	new = malloc(sizeof(t_cmd_ex));
	if (!new)
	{
		perror("malloc");
		my_close(fd_in, fd_out, "close in child after malloc error");
		exit(EXIT_FAILURE);
	}
	new->fd_in = fd_in;
	new->fd_out = fd_out;
	new->path = NULL;
	new->args = ex->cmds->args;
	new->mini = ex->mini;
	return (new);
}

// Opens files and fills the array

void	open_files(char *file_in, char *file_out, int *filefds)
{
	int	temp_fd;

	temp_fd = open(file_in, O_RDONLY);
	if (temp_fd == -1)
		handle_err(errno, "open infile");
	filefds[0] = temp_fd;
	temp_fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (temp_fd == -1)
	{
		perror("open outfile");
		if (close(filefds[1]) == -1)
			perror("close infile");
		exit(EXIT_FAILURE);
	}
	filefds[1] = temp_fd;
}
