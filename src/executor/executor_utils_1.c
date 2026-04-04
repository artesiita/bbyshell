/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:52 by bcanals-          #+#    #+#             */
/*   Updated: 2026/04/04 08:41:50 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// quick line to close 2 fds and print the errors if there are any

void	my_close(int *fd1, int *fd2, char *msg)
{
	if (*fd1 > 2 )
	{
		if (close(*fd1) == -1)
			perror(msg);
		*fd1 = -1;
	}
	if (*fd2 > 2)
	{
		if (close(*fd2) == -1)
			perror(msg);
		*fd2 = -1;
	}
}

// Manages the dup2 with its error handlings

int	redirect(t_mini *mini)
{
	if ((dup2(mini->ex->fds[OLD_FDS][P_READ], STDIN_FILENO) == -1) ||
	 (dup2(mini->ex->fds[NEW_FDS][P_WRITE], STDOUT_FILENO) == -1) )
		return (0);
	return (1);
}

// Waits for all the child pid_t processes

void	wait_childs(pid_t *childs)
{
	while (childs && *childs)
		if (waitpid(*childs++, NULL, 0) == -1)
			perror("waitpid");
}

void	ft_del_t_hd_data(void *void_node)
{
	t_hd_data	*node;

	node = (t_hd_data *)void_node;
	free(node->line);
	node->next = NULL;
	free(node);
}

void	ft_del_t_hedoc(void *void_node)
{
	t_hedoc	*node;

	node = (t_hedoc *)void_node;
	ft_lstclear((void **)&(node->data), &ft_del_t_hd_data);
	node->data = NULL;
	node->next = NULL;
	free(node);
}

void	ft_postex_clean(t_mini *mini)
{
	free_parsing(mini);
	mini->ex->cur_cmd = NULL;
	ft_lstclear((void **)&(mini->ex->hedocs), &ft_del_t_hedoc);
	my_close(&(mini->ex->fds[OLD_FDS][P_WRITE]),
			&(mini->ex->fds[OLD_FDS][P_READ]), "close in cleanup");
	my_close(&(mini->ex->fds[NEW_FDS][P_WRITE]),
			&(mini->ex->fds[NEW_FDS][P_READ]), "close in cleanup");
}
