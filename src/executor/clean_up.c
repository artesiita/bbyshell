/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becanals <becanals@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:26:28 by becanals          #+#    #+#             */
/*   Updated: 2026/04/19 17:21:20 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Cleaner to be called just before ending executor
*/

void	ft_postex_clean(t_mini *mini)
{
	free_parsing(mini);
	mini->ex->cur_cmd = NULL;
	my_close(&(mini->ex->fds[OLD_FDS][P_WRITE]),
			&(mini->ex->fds[OLD_FDS][P_READ]), "close in cleanup");
	my_close(&(mini->ex->fds[NEW_FDS][P_WRITE]),
			&(mini->ex->fds[NEW_FDS][P_READ]), "close in cleanup");
	if (mini->ex->childs)
	{
		free(mini->ex->childs);
		mini->ex->childs = NULL;
	}
}

/*
	Cleaner to be called in executor fails and errors
*/

void	ex_exit(t_mini *mini, int status)
{
	ft_postex_clean(mini);
	free_everything(mini);
	exit(status);
}
