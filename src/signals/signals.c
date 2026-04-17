/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laiaartes <laiaartes@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:16:47 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/13 19:42:06 by laiaartes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_signal_value = 0;

void	sig_int_c(int sign)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_value = sign;
}

void	sig_nonint_c(int sign)
{
	printf("\n");
	rl_on_new_line();
	g_signal_value = sign;
}

void	signals_intmode(void)
{
	signal(SIGINT, sig_int_c);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_nonintmode(void)
{
	signal(SIGINT, sig_nonint_c);
	signal(SIGQUIT, sig_nonint_c);
}
