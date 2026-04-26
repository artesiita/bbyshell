/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:23:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/26 15:51:32 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	load_mini(t_mini *mini, t_executor *ex, char **env);
static void	mini_loop(t_mini *mini);
static void	manage_tokens(t_mini *mini);
static int	manage_heredocs(t_mini *mini);

int	main(int ac, char **av, char **env)
{
	t_mini		mini;
	t_executor	ex;

	(void)ac;
	(void)av;
	if (!load_mini(&mini, &ex, env))
		return (0);
	mini_loop(&mini);
	clear_history();
	free_env(mini.env_head);
	return (0);
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
			if (manage_heredocs(mini))
			{
				expansions(mini);
				manage_tokens(mini);
			}
			free_tokens(mini->tokens);
			mini->tokens = NULL;
			free(line);
		}
	}
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
	if (mini->saved_stdin == -1 || mini->saved_stdout == -1)
		return (0);
	return (1);
}

static void	manage_tokens(t_mini *mini)
{
	if (mini->tokens)
	{
		mini->cmds = parsing(mini);
		if (!mini->cmds)
			free_parsing(mini);
		else
			ft_executor(mini);
	}
}

static int	manage_heredocs(t_mini *mini)
{
	if (heredoc_input(mini) == EXIT_FROM_SIGNAL)
	{
		free_tokens(mini->tokens);
		mini->tokens = NULL;
		mini->exit_status = 130;
		return (0);
	}
	return (1);
}
