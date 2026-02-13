/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:10:40 by lartes-s          #+#    #+#             */
/*   Updated: 2026/02/13 17:18:56 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_redirection(t_cmds *node, t_token *cur, t_mini *mini)
{
	t_redir	*redir;
	t_redir	*tmp;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		fatal_error(mini, "minishell: malloc: cannot allocate memory", 1);
	redir->type = (t_redir_type)cur->type;
	redir->target = ft_strdup(cur->next->content);
	redir->next = NULL;
	if (node->redirs == NULL)
		node->redirs = redir;
	else
	{
		tmp = node->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

int	fill_args(t_cmds *node, t_token *cur, t_mini *mini)
{
	int	i;

	i = 0;
	while (cur && cur->type != T_PIPE)
	{
		if (cur->type == T_WORD)
		{
			node->args[i] = ft_strdup(cur->content);
			i++;
			cur = cur->next;
		}
		else
		{
			if (!cur->next || cur->next->type != T_WORD)
			{
				printf("Bbyshell: syntax error\n");
				return (0);
			}
			parse_redirection(node, cur, mini);
			cur = cur->next;
			if (cur)
				cur = cur->next;
		}
	}
	return (1);
}

t_cmds	*parsing(t_mini *mini)
{
	t_token	*cur;
	t_cmds	*head;
	t_cmds	*new_node;

	cur = mini->tokens;
	head = NULL;
	if (cur && cur->type == T_PIPE)
	{
		printf("Bbyshell: syntax error\n");
		mini->exit_status = 2;
		return (NULL);
	}
	while (cur)
	{
		new_node = ft_calloc(1, sizeof(t_cmds));
		if (!new_node)
			fatal_error(mini, "minishell: malloc: cannot allocate memory", 1);
		new_node->args = ft_calloc(commands_counter(cur) + 1, sizeof(char *));
		if (!fill_args(new_node, cur, mini))
		{
			mini->exit_status = 2;
			return (NULL);
		}
		add_command_node(&head, new_node);
		while (cur && cur->type != T_PIPE)
			cur = cur->next;
		if (cur && cur->type == T_PIPE)
		{
			if (!cur->next || cur->next->type == T_PIPE)
			{
				printf("Bbyshell: syntax error\n");
				mini->exit_status = 2;
				return (NULL);
			}
			cur = cur->next;
		}
	}
	return (head);
}
