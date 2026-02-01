/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becanals <becanals@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:25:50 by becanals          #+#    #+#             */
/*   Updated: 2026/02/01 18:11:36 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

// Handles the forking process and manages errors

pid_t	my_fork(char **cmd, char **env, int **fds, pid_t *childs)
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

pid_t	*do_childs(int **fds, t_mini *mini)
{
	pid_t	*childs;
	t_cmds	*cmds;
	int		cmd_num;/*elements in cmd list*/

	cmds  = mini->cmds;
	childs = ft_calloc(cmd_num, sizeof(pid_t));
	//if (!childs)
	//	close_exit(fds[1], errno, "ft_calloc");
	while (cmds)
	{
		//if (pipe(fds[0]) == -1)
		//	free_close_exit(fds[1], NULL, childs, "pipe");
		childs[i] = my_fork(cmds->args, mini->env, fds, childs);
		//if (childs[i] == -1)
		//	free_close_exit(fds[1], fds[0], childs, "fork");
		my_close(fds[1][0], fds[1][1], "close in main proc after forking");
		fds[1][0] = fds[0][0];
		fds[1][1] = fds[0][1];
		i++;
	}
	return (childs);
}

void	cmd_handler(t_mini *mini);
{
	int		oldfds[2];
	int		newfds[2];
	int		*fds[2];
	pid_t	*childs;

	fds[0] = newfds;
	fds[1] = oldfds;
	//open_files(argv[1], argv[argc - 1], oldfds);
	childs = do_childs(fds, mini);
	//open_files(argv[1], argv[argc - 1], newfds);

	childs[argc - 4] = my_fork(argv[argc - 2], env, fds, childs);
	if (childs[argc - 4] == -1)
		free_close_exit(oldfds, newfds, childs, "fork");
	my_close(oldfds[0], oldfds[1], "olds");
	my_close(newfds[0], newfds[1], "news");
	wait_childs(childs);
	free(childs);
}
