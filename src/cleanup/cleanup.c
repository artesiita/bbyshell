/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:28:29 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/19 16:58:33 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_everything(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->env_head)
		free_env(mini->env_head);
	mini->env_head = NULL; // Crucial
	if (mini->tokens)
		free_tokens(mini->tokens);
	mini->tokens = NULL;
	if (mini->cmds)
		free_commands(mini->cmds);
	mini->cmds = NULL;
	close(mini->saved_stdin);
	close(mini->saved_stdout);
	if (mini->ex)
	{
		if (mini->ex->childs)
			free(mini->ex->childs);
		mini->ex->childs = NULL;
	}
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

void	ft_del_t_heredoc(void *void_node)
{
	t_heredoc	*node;

	node = (t_heredoc *)void_node;
	if (node->line)
		free(node->line);
	node->line = NULL;
	node->next = NULL;
}
