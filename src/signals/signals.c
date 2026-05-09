/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:16:47 by lartes-s          #+#    #+#             */
/*   Updated: 2026/05/09 14:25:25 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_signal_value = 0;

void	handle_bs_signal(t_mini *mini)
{
	if (g_signal_value == SIGQUIT)
	{
		mini->exit_status = 131;
		g_signal_value = 0;
	}
}

void	handle_c_signal(t_mini *mini)
{
	if (g_signal_value == SIGINT)
	{
		mini->exit_status = 130;
		g_signal_value = 0;
	}
}

void	sig_int_c(int sign)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_value = sign;
}

void	signals_intmode(void)
{
	signal(SIGINT, sig_int_c);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_nonintmode(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
