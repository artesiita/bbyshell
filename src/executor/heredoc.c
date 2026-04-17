/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laiaartes <laiaartes@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:50:47 by becanals          #+#    #+#             */
/*   Updated: 2026/04/13 22:11:38 by laiaartes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Aquesta l'únic que ha de fer és agafar un heredoc que ja haurà estat creat a set_heredoc
// i gestionar el filling de les línies que introdueixi l'usuari cap a la linked list

void add_hedoc_back(t_hedoc **list, t_hedoc *new)
{
    t_hedoc *curr;

    if (!list || !new)
        return;
    if (!*list)
    {
        *list = new;
        return;
    }
    curr = *list;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
}

void add_hd_data_back(t_hd_data **list, t_hd_data *new)
{
    t_hd_data *curr;

    if (!list || !new)
        return;
    if (!*list)
    {
        *list = new;
        return;
    }
    curr = *list;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
}

static void	fill_heredoc(t_hedoc *heredoc, char *end)
{
	char		*line;
	t_hd_data	*new_node;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_streq(line, end))
		{
			free(line);
			break;
		}
		new_node = ft_calloc(1, sizeof(t_hd_data));
		if (!new_node)
		{
			free(line);
			return ; 
		}
		new_node->line = line;
		new_node->next = NULL;
		add_hd_data_back(&(heredoc->data), new_node);
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
		return ;
	fill_heredoc(current, end);
	add_hedoc_back(&(mini->ex->hedocs), current);
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
	fd = mini->ex->fds[OLD_FDS][P_WRITE];
	my_id = fork();
	if (my_id == -1)
		return ; 
	else if (my_id == 0)
	{
		data = heredoc->data;
		close(mini->ex->fds[OLD_FDS][P_READ]);
		while (data)
		{
			if (data->line)
			{
				write(fd, data->line, ft_strlen(data->line));
				write(fd, "\n", 1);
			}
			data = data->next;
		}
		close(fd);
		exit(EXIT_SUCCESS);
	}
	close(fd);
	mini->ex->fds[OLD_FDS][P_WRITE] = -1;
	waitpid(my_id, NULL, 0);
}

//static void	clean_heredoc()
//{}

//static void 
