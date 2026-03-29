/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becanals <becanals@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:50:47 by becanals          #+#    #+#             */
/*   Updated: 2026/03/29 12:34:09 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Aquesta l'únic que ha de fer és agafar un heredoc que ja haurà estat creat a set_heredoc
// i gestionar el filling de les línies que introdueixi l'usuari cap a la linked list

static void	fill_heredoc(t_hedoc *heredoc, char *end)
{
	char	*line;
	void	*new;

	line = readline("> ");
	while (!ft_streq(line, end))
	{
		new = ft_lstnew(sizeof(t_hd_data), line);
		//printf("linia: %p\n", line);
		//printf("guardada a: %p\n", ((t_hd_data *)new)->line);
		if (!new)
			return ; // Aquí faltarà fer el clear i tot això		
		ft_lstadd_back((void **)&(heredoc->data), new);
		line = readline(">");
	}
}

// set_heredoc reb un end i ha de preparar la configuració del heredoc, la creació dels
// structs que calgui a executor i tot això
// Ha de cridar fill_heredoc perquè faci el filling per part de l'usuari

void	set_heredoc(t_mini *mini, char *end)
{
	t_hedoc *current;
	
	current = ft_calloc(1, sizeof(t_hedoc));
	if (!current)
		return ; //falta gestionar l'error de malloc
	fill_heredoc(current, end);
	if (current->data->line)
		write(1, current->data->line, 1);
	ft_lstadd_back((void **)&(mini->ex->hedocs), current);
}

// dump_heredoc s'encarrega d'escriure el contingut de l'últim heredoc a l'extrem
// de la pipe que el comando llegirà. Ho fa en un subprocés per evitar que la pipe
// es quedi saturada.

void	dump_heredoc(t_mini *mini)
{
	pid_t		my_id;
	t_hedoc		*heredoc;
	t_hd_data	*data;
	int			fd;

	heredoc = ft_lstlast(mini->ex->hedocs);
	if (!heredoc)
		return ;
	my_id = fork();
	if (my_id == -1)
		return ; //gestionar error??
	else if (my_id == 0)
	{
		//printf("hola soc el fill\n");
		data = heredoc->data;
		fd = mini->ex->fds[OLD_FDS][P_WRITE];
		close(mini->ex->fds[OLD_FDS][P_READ]);
		while (data)
		{
			//printf("fill: dins del while\n");
			//printf("fill: ready x imprimir %p\n", data->line);
			write(fd, data->line, ft_strlen(data->line));
			write(fd, "\n", 1);
			//write(2, "he escrit \n", 10);
			data = data->next;
		}
		close(fd);
		//printf("adeu soc el fill\n");
		// pensar si cal algun cleanup aqui
		exit(EXIT_SUCCESS);
	}
	close(mini->ex->fds[OLD_FDS][P_WRITE]);
	return ;
}

//static void	clean_heredoc()
//{}

//static void 
