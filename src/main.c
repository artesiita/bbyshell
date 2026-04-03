/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:23:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/03 18:42:46 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	load_mini(t_mini *mini, t_executor *ex, char **env);
static void	mini_loop(t_mini *mini);

int	main(int ac, char **av, char **env)
{
	t_mini		mini;
	t_executor 	ex;

	(void)ac;
	(void)av;
	if (load_mini(&mini, &ex, env))
	{
		// gestió d'errors (potser directament dins de load_mini? i aquí sortim i ja
	}
	// Aquí hi faltarà la configuració de senyals
	mini_loop(&mini);
	clear_history();
	free_env(mini.env_head);
	return (0);
}

static int	load_mini(t_mini *mini, t_executor *ex, char **env)
{
	if (!env_setup(mini, env))
		return (0);
	mini->ex = ex;
	mini->ex->hedocs = NULL;
	mini->tokens = NULL;
	mini->cmds = NULL;
	mini->exit_status = 0;
	return (1);
}

static void	mini_loop(t_mini *mini)
{
	char		*line;

	while (1)
	{
		signals_intmode();
		line = readline(PROMPT);
		if (!line)
		{
			printf("exit\n"); // això no hauria de tirar error?
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			mini->tokens = lexer(mini, line);
			expansions(mini);
			if (mini->tokens)
			{
				mini->cmds = parsing(mini);
				if (!mini->cmds)
					free_parsing(mini);
				else
					ft_executor(mini);
			}
		}
		free(line);
	}
}
