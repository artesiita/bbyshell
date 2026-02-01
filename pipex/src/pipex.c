/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:15:12 by bizcru            #+#    #+#             */
/*   Updated: 2025/12/07 12:11:13 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	my_fork(char *cmd, char **env, int *fds_in, int *fds_out)
{
	pid_t	my_id;
	t_data	*data;

	my_id = fork();
	if (my_id == -1)
		handle_err(errno, "fork", EXIT_FAILURE);
	else if (my_id == 0)
	{
		my_close(fds_in[1], fds_out[0]);
		data = load_data(cmd, env, fds_in[0], fds_out[1]);
		redirect(data);
		if (data->fd_out != -1 && data->fd_in != -1
			&& execve(data->path, data->args, env) == -1)
			clean_exit(data, errno, "execve", EXIT_FAILURE);
		my_close(data->fd_in, data->fd_out);
		if (data->fd_out == -1 || data->fd_in == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	return (my_id);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefds[2];
	int		filefds[2];
	pid_t	pid[2];
	int		err_num;

	if (argc != 5)
		handle_err(0, "Please write 4 arguments", EXIT_FAILURE);
	if (pipe(pipefds) == -1)
		handle_err(errno, "pipe error", EXIT_FAILURE);
	open_files(argv[1], argv[4], filefds);
	pid[0] = my_fork(argv[2], env, filefds, pipefds);
	pid[1] = my_fork(argv[3], env, pipefds, filefds);
	my_close(filefds[0], filefds[1]);
	my_close(pipefds[0], pipefds[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &err_num, 0);
	exit(err_num >> 8);
}
