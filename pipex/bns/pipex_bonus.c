/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:15:12 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/14 17:25:25 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Handles the forking process and manages errors

pid_t	my_fork(char *cmd, char **env, int **fds, pid_t *childs)
{
	pid_t	my_id;
	t_data	*data;

	my_id = fork();
	if (my_id == -1)
		return (my_id);
	else if (my_id == 0)
	{
		free(childs);
		my_close(fds[1][1], fds[0][0], "close in child pre execve");
		data = load_data(cmd, env, fds[1][0], fds[0][1]);
		redirect(data);
		if (execve(data->path, data->args, env) == -1)
			clean_exit(data, errno, "execve");
		my_close(data->fd_in, data->fd_out, "close in child afer execve");
		printf("exit amb exit: %i", getpid());
		exit(EXIT_SUCCESS);
	}
	return (my_id);
}

// Handles the iteration of creating a child process for each cmd

pid_t	*do_childs(int **fds, int argc, char **argv, char **env)
{
	int		i;
	pid_t	*childs;

	childs = ft_calloc(argc - 2, sizeof(pid_t));
	if (!childs)
		close_exit(fds[1], errno, "ft_calloc");
	i = 0;
	while (i < argc - 4)
	{
		if (pipe(fds[0]) == -1)
			free_close_exit(fds[1], NULL, childs, "pipe");
		childs[i] = my_fork(argv[i + 2], env, fds, childs);
		if (childs[i] == -1)
			free_close_exit(fds[1], fds[0], childs, "fork");
		my_close(fds[1][0], fds[1][1], "close in main proc after forking");
		fds[1][0] = fds[0][0];
		fds[1][1] = fds[0][1];
		i++;
	}
	return (childs);
}

int	main(int argc, char **argv, char **env)
{
	int		oldfds[2];
	int		newfds[2];
	int		*fds[2];
	pid_t	*childs;

	fds[0] = newfds;
	fds[1] = oldfds;
	if (argc < 5)
		handle_err(0, "Please write at least 4 arguments");
	open_files(argv[1], argv[argc - 1], oldfds);
	childs = do_childs(fds, argc, argv, env);
	open_files(argv[1], argv[argc - 1], newfds);
	childs[argc - 4] = my_fork(argv[argc - 2], env, fds, childs);
	if (childs[argc - 4] == -1)
		free_close_exit(oldfds, newfds, childs, "fork");
	my_close(oldfds[0], oldfds[1], "olds");
	my_close(newfds[0], newfds[1], "news");
	wait_childs(childs);
	free(childs);
}
