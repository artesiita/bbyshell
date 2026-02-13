#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mini mini;
	char *line;

	(void)ac;
	(void)av;

	mini.env = env_setup(env);
	mini.tokens = NULL;
	mini.cmds = NULL;
	mini.exit_status = 0;

	while (1)
	{
		line = readline("bbyshell> ");
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
				if (mini.cmds)
					print_cmds(mini.cmds);
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
	free_env(mini.env);
	return (0);
}