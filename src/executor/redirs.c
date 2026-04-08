/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becanals <becanals@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:11:14 by becanals          #+#    #+#             */
/*   Updated: 2026/04/08 21:45:35 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_redir_in(t_mini *mini, t_redir *redir)
{
	if (mini->ex->fds[OLD_FDS][P_READ] > 2)
		close(mini->ex->fds[OLD_FDS][P_READ]);
	mini->ex->fds[OLD_FDS][P_READ] = open(redir->target, O_RDONLY);
}

void ft_redir_out(t_mini *mini, t_redir *redir)
{
	if (mini->ex->fds[NEW_FDS][P_WRITE] > 2)
		close(mini->ex->fds[NEW_FDS][P_WRITE]);
	mini->ex->fds[NEW_FDS][P_WRITE] = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void ft_redir_heredoc(t_mini *mini, t_redir *redir)
{
	if (mini->ex->fds[OLD_FDS][P_READ] > 2)
		close(mini->ex->fds[OLD_FDS][P_READ]);
	mini->ex->fds[OLD_FDS][P_READ] = 1;
	if (pipe(mini->ex->fds[OLD_FDS]) == -1)
		return ; // Falta gestionar aquest error
	set_heredoc(mini, redir->target);
}

void ft_redir_append(t_mini *mini, t_redir *redir)
{
	if (mini->ex->fds[NEW_FDS][P_WRITE] > 2)
		close(mini->ex->fds[NEW_FDS][P_WRITE]);
	mini->ex->fds[NEW_FDS][P_WRITE] = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
}
