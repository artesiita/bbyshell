/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becanals <becanals@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:50:47 by becanals          #+#    #+#             */
/*   Updated: 2026/03/22 15:08:10 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	fill_heredoc()
{
	// Aquesta l'únic que ha de fer és agafar un heredoc que ja haurà estat creat a set_heredoc
	// i gestionar el filling de les línies que introdueixi l'usuari cap a la linked list 
}

void	set_heredoc(t_mini *mini, char *end)
{
	// Aquesta funció reb un end i ha de preparar la configuració del heredoc, la creació dels
	// structs que calgui a executor i tot això
	// Ha de cridar fill_heredoc perquè faci el filling per part de l'usuari
}



//static void	clean_heredoc()
//{}

//static void 
