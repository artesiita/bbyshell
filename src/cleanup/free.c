/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:29:08 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/26 15:18:03 by lartes-s         ###   ########.fr       */
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
		redirs->target = NULL;
		if (redirs->hd)
		{
			free_hd(redirs->hd);
			redirs->hd = NULL;
		}
		redirs = NULL;
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
		cmds->args = NULL;
		if (cmds->redirs)
			free_redirs(cmds->redirs);
		cmds->redirs = NULL;
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
		env->key = NULL;
		free(env->value);
		env->value = NULL;
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
			free_hd(head->hd);
			head->hd = NULL;
		}
		head = temp;
	}
}
