/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laiaartes <laiaartes@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:11:14 by becanals          #+#    #+#             */
/*   Updated: 2026/04/13 19:53:03 by laiaartes        ###   ########.fr       */
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
	int	hd_pipe[2];
	if (mini->ex->fds[OLD_FDS][P_READ] > 2)
		close(mini->ex->fds[OLD_FDS][P_READ]);
	
	if (pipe(hd_pipe) == -1)
	{
		perror("minishell: pipe");
		return ;
	}
	mini->ex->fds[OLD_FDS][P_READ] = hd_pipe[0];
	mini->ex->fds[OLD_FDS][P_WRITE] = hd_pipe[1];
	
	set_heredoc(mini, redir->target);
}

void ft_redir_append(t_mini *mini, t_redir *redir)
{
	if (mini->ex->fds[NEW_FDS][P_WRITE] > 2)
		close(mini->ex->fds[NEW_FDS][P_WRITE]);
	mini->ex->fds[NEW_FDS][P_WRITE] = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
}
