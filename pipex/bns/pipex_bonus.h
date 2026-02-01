/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:18:40 by bizcru            #+#    #+#             */
/*   Updated: 2024/12/14 16:43:41 by bcanals-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char	*path;
	char	**args;
	int		fd_in;
	int		fd_out;
}			t_data;

void	my_close(int fd1, int fd2, char *msg);
void	clean(t_data *data);
void	clean_exit(t_data *data, int my_errno, char *msg);
void	handle_err(int my_errno, char *msg);
void	redirect(t_data *data);
t_data	*load_data(char *cmd, char **env, int fd_in, int fd_out);
void	open_files(char *file_in, char *file_out, int *filefds);
void	close_exit(int *fds, int my_errno, char *msg);
void	free_close_exit(int *fds1, int *fds2, pid_t *childs, char *msg);
void	wait_childs(pid_t *childs);
#endif
