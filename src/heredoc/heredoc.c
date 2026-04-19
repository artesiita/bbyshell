/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:50:47 by becanals          #+#    #+#             */
/*   Updated: 2026/04/19 15:59:18 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Aquesta l'únic que ha de fer és agafar un heredoc que ja haurà estat creat a set_heredoc
// i gestionar el filling de les línies que introdueixi l'usuari cap a la linked list

void	fill_heredoc(t_heredoc **hd, char *end)
{
	char	*line;
	void	*new;

	line = readline("> ");
	while (!ft_streq(line, end))
	{
		new = ft_lstnew(sizeof(t_heredoc), line);
		//printf("linia: %p\n", line);
		//printf("guardada a: %p\n", ((t_hd_data *)new)->line);
		if (!new)
			return ; // Aquí faltarà fer el clear i tot això		
		ft_lstadd_back((void **)hd, new);
		line = readline("> ");
	}
}

static  t_heredoc	*get_last_hd(t_mini *mini)
{
	t_heredoc	*hd;
	t_redir		*redir;

	hd = NULL;
	redir =  mini->ex->cur_cmd->redirs;
	while (redir)
	{
		if (redir->type == R_HEREDOC)
			hd = redir->hd;
		redir = redir->next;
	}
}

// dump_heredoc s'encarrega d'escriure el contingut de l'últim heredoc a l'extrem
// de la pipe que el comando llegirà. Ho fa en un subprocés per evitar que la pipe
// es quedi saturada.

void	dump_heredoc(t_mini *mini)
{
	pid_t			my_id;
	int				fd;
	t_heredoc	*hd;

	hd = get_last_hd(mini);
	if (!hd)
		return ;
	my_id = fork();
	if (my_id == -1)
		return ; //gestionar error??
	else if (my_id == 0)
	{
		//printf("procés %i = heredoc dumper\n", getpid());
		fd = mini->ex->fds[OLD_FDS][P_WRITE];
		while (hd)
		{
			write(fd, hd->line, ft_strlen(hd->line));
			write(fd, "\n", 1);
			hd = hd->next;
		}
		ex_exit(mini, EXIT_SUCCESS);
	}
	my_close(&(mini->ex->fds[OLD_FDS][P_WRITE]), NULL, "");
	return ;
}

//static void	clean_heredoc()
//{}

//static void 
