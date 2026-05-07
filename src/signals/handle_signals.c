/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:31:50 by lartes-s          #+#    #+#             */
/*   Updated: 2026/05/07 19:32:54 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
