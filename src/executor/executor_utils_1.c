/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laiaartes <laiaartes@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:48:52 by bcanals-          #+#    #+#             */
/*   Updated: 2026/04/13 21:01:14 by laiaartes        ###   ########.fr       */
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

	if (!void_node)
		return ;
	node = (t_hd_data *)void_node;
	if (node->line)
		free(node->line);
	free(node);
}

void	ft_del_t_hedoc(void *void_node)
{
	t_hedoc		*node;
	t_hd_data	*data;
	t_hd_data	*tmp;

	node = (t_hedoc *)void_node;
	data = node->data;
	while (data)
	{
		tmp = data->next;
		free(data->line);
		free(data);
		data = tmp;
	}
	free(node);
}


void	ft_postex_clean(t_mini *mini)
{
	t_hedoc *curr;
	t_hedoc *next;

	free_parsing(mini);
	mini->ex->cur_cmd = NULL;
	curr = mini->ex->hedocs;
	while (curr)
	{
		next = curr->next;
		ft_del_t_hedoc(curr);
		curr = next;
	}
	mini->ex->hedocs = NULL;

	my_close(&(mini->ex->fds[OLD_FDS][P_WRITE]),
			&(mini->ex->fds[OLD_FDS][P_READ]), "close in cleanup");
	my_close(&(mini->ex->fds[NEW_FDS][P_WRITE]),
			&(mini->ex->fds[NEW_FDS][P_READ]), "close in cleanup");
}
