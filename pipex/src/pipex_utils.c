/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:52 by bcanals-          #+#    #+#             */
/*   Updated: 2025/12/07 11:49:04 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// quick line to close 2 fds and print the errors if there are any

void	my_close(int fd1, int fd2)
{
	if (fd1 != -1 && close(fd1) == -1)
		perror("close");
	if (fd2 != -1 && close(fd2) == -1)
		perror("close");
}

// Frees the data of a t_data
// Checks which one is available to avoid double free in load_data

void	clean(t_data *data)
{
	my_close(data->fd_in, data->fd_out);
	if (data->path == data->args[0])
		data->path = 0;
	if (data->path)
		free(data->path);
	if (data->args)
		ft_free_array(data->args);
	free(data);
}

// Frees the data in t_data and exits the code via handl_err

void	clean_exit(t_data *data, int my_errno, char *msg, int status)
{
	clean(data);
	handle_err(my_errno, msg, status);
}

// Exits the process previously printing the error msg

void	handle_err(int my_errno, char *msg, int status)
{
	errno = my_errno;
	if (my_errno)
		perror(msg);
	else
		ft_putstr_fd(msg, 2);
	exit(status);
}

// Manages the dup2 with its error handlings

void	redirect(t_data *data)
{
	if (data->fd_in != -1 && dup2(data->fd_in, STDIN_FILENO) == -1)
		clean_exit(data, errno, "dup2", EXIT_FAILURE);
	if (data->fd_out != -1 && dup2(data->fd_out, STDOUT_FILENO) == -1)
		clean_exit(data, errno, "dup2", EXIT_FAILURE);
}
