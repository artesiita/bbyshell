/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:28:29 by lartes-s          #+#    #+#             */
/*   Updated: 2026/02/13 17:28:55 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_everything(t_mini *mini)
{
	free_env(&mini->env);
	free_tokens(&mini->tokens);
	free_commands(&mini->cmds);
}

void	fatal_error(t_mini *mini, char *msg, int status)
{
	if (msg)
		perror(msg);
	free_everything(mini);
	exit(status);
}
