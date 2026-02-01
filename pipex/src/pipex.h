/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bizcru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:18:40 by bizcru            #+#    #+#             */
/*   Updated: 2025/12/05 19:29:22 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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

void	my_close(int fd1, int fd2);
void	clean(t_data *data);
void	clean_exit(t_data *data, int my_errno, char *msg, int status);
void	handle_err(int my_errno, char *msg, int status);
void	redirect(t_data *data);
t_data	*load_data(char *cmd, char **env, int fd_in, int fd_out);
void	open_files(char *file_in, char *file_out, int *filefds);
#endif
