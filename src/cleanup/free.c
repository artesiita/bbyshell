/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:29:08 by lartes-s          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/26 12:37:24 by lartes-s         ###   ########.fr       */
=======
/*   Updated: 2026/04/26 12:29:52 by becanals         ###   ########.fr       */
>>>>>>> origin/heredoc
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_str_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		free(redirs->target);
		if (redirs->hd)
			ft_lstclear((void **)&(redirs->hd), &ft_del_t_heredoc);
		redirs->hd = NULL;
		free(redirs);
		redirs = tmp;
	}
}

void	free_commands(t_cmds *cmds)
{
	t_cmds	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_str_array(cmds->args);
		if (cmds->redirs)
			free_redirs(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head->next;
		if (head->content)
			free(head->content);
		if (head->hd)
		{
			ft_lstclear((void **)&(head->hd), &ft_del_t_heredoc);
			head->hd = NULL;
		}
		free(head);
		head = temp;
	}
	head = NULL;
}
