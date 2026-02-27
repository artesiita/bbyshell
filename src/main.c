/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:23:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/02/27 17:58:00 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	char	*line;

	(void)ac;
	(void)av;
	env_setup(&mini, env);
	mini.tokens = NULL;
	mini.cmds = NULL;
	mini.exit_status = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			mini.tokens = lexer(line);
			if (mini.tokens)
			{
				mini.cmds = parsing(&mini);
				// print_tokens(mini.tokens);
				cmd_handler(&mini);
				free_tokens(&mini.tokens);
				mini.tokens = NULL;
				if (mini.cmds)
				{
					free_commands(&mini.cmds);
					mini.cmds = NULL;
				}
			}
		}
		free(line);
	}
	clear_history();
	free_env(&mini.env_head);
	return (0);
}
