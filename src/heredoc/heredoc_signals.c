/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:08:13 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/25 19:36:03 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_signal_interrupt(char *line, int *exit_from_signal)
{
	if (g_signal_value == SIGINT)
	{
		if (line)
			free(line);
		*exit_from_signal = EXIT_FROM_SIGNAL;
		return (1);
	}
	return (0);
}

void	set_heresign_int(int sign)
{
	g_signal_value = sign;
	//write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	signals_heremode(void)
{
	struct sigaction	sa_int;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = set_heresign_int;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_heresignals(int *exit_from_signal)
{
	*exit_from_signal = 0;
	g_signal_value = 0;
	signals_heremode();
}