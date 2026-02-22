/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:52 by bcanals-          #+#    #+#             */
/*   Updated: 2026/02/22 16:58:54 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// quick line to close 2 fds and print the errors if there are any

void	my_close(int fd1, int fd2, char *msg)
{
	if (fd1 > 2 && close(fd1) == -1)
		perror(msg);
	if (fd2 > 2 && close(fd2) == -1)
		perror(msg);
}

// Frees the data of a t_cmd_ex
// Checks which one is available to avoid double free in load_data

void	clean(t_cmd_ex *data)
{
	// my_close(data->fd_in, data->fd_out, "close in child after error");
	if (data->path)
		free(data->path);
	// if (data->args)
	//	ft_free_array(data->args);
	free(data);
}

// Frees the data in t_cmd_ex and exits the code via handl_err

void	clean_exit(t_cmd_ex *data, int my_errno, char *msg)
{
	clean(data);
	handle_err(my_errno, msg);
}

// Exits the process previously printing the error msg

void	handle_err(int my_errno, char *msg)
{
	errno = my_errno;
	if (my_errno)
		perror(msg);
	else
		ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

// Manages the dup2 with its error handlings

void	redirect(t_cmd_ex *data)
{
	if (dup2(data->fd_in, STDIN_FILENO) == -1)
		clean_exit(data, errno, "dup2");
	if (dup2(data->fd_out, STDOUT_FILENO) == -1)
		clean_exit(data, errno, "dup2");
}
