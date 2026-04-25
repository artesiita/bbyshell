/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:23:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/25 16:21:22 by lartes-s         ###   ########.fr       */
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
	mini_loop(&mini);
	clear_history();
	free_env(mini.env_head);
	return (0);
}

static int	load_mini(t_mini *mini, t_executor *ex, char **env)
{
	ft_memset(ex, 0, sizeof(t_executor));
	if (!env_setup(mini, env))
		return (0);
	mini->ex = ex;
	mini->ex->childs = NULL;
	mini->ex->cur_cmd = NULL;
	mini->tokens = NULL;
	mini->cmds = NULL;
	mini->exit_status = 0;
	mini->saved_stdin = dup(STDIN_FILENO);
	mini->saved_stdout = dup(STDOUT_FILENO);
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
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			mini->tokens = lexer(mini, line);
			if (heredoc_input(mini) == ERROR)
			{
				free_tokens(mini->tokens);
				mini->tokens = NULL;
			}
			else
				expansions(mini);
			if (mini->tokens)
			{
				mini->cmds = parsing(mini);
				if (!mini->cmds)
					free_parsing(mini);
				else
					ft_executor(mini);
			}
			free(line);
		}
	}
}
