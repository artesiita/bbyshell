/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:28:29 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/11 14:20:39 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_everything(t_mini *mini)
{
	if (mini->env_head)
	{
		free_env(mini->env_head);
		mini->env_head = NULL;
	}
	if (mini->tokens)
		free_tokens(mini->tokens);
	if (mini->cmds)
		free_commands(mini->cmds);
	if (mini->ex && mini->ex->childs)
	{
		free(mini->ex->childs);
		mini->ex->childs = NULL;
	}
	mini->tokens = NULL;
	mini->cmds = NULL;
}

void	free_parsing(t_mini *mini)
{
	free_tokens(mini->tokens);
	free_commands(mini->cmds);
	mini->tokens = NULL;
	mini->cmds = NULL;
}

void	fatal_error(t_mini *mini, char *msg, int status)
{
	if (msg)
		perror(msg);
	free_everything(mini);
	exit(status);
}
