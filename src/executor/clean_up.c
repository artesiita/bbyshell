/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becanals <becanals@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:26:28 by becanals          #+#    #+#             */
/*   Updated: 2026/04/19 16:49:31 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	OBSOLETE: cleaner of t_hd_data node;


ft_lstclear((void **)&(mini->ex->hedocs), &ft_del_t_hedoc);

void	ft_del_t_hd_data(void *void_node)
{
	t_hd_data	*node;

	node = (t_hd_data *)void_node;
	if (node->line)
		free(node->line);
	node->line = NULL;
	node->next = NULL;
}
*/
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
	free_env(mini->env_head);
	mini->env_head = NULL;
	mini->exit_status = status;
	exit(status);
}
