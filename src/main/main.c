
#include "inc/minishell.h"

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->value)
		{
			printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
}

void print_array(char **array)
{
	int	i;

	i = -1;
	while (array[i++])
		printf("%s\n", array[i]);
}

void my_cmd_parser(t_mini  *mini, char **cmds)
{
	int	i = -1;
	t_cmds *cmd;
	t_cmds *next;
	t_cmds *cmd_list = NULL;

	while (cmds[++i])
	{
		cmd = ft_calloc(sizeof(t_cmds), 1);
		cmd->args = ft_split(cmds[i], ' ');
		cmd->redirs = NULL;
		cmd->next = NULL;
		if (!cmd_list)
			cmd_list = cmd;
		else
		{
			next = cmd_list;
			while (next->next)
				next = next->next;
			next->next = cmd; 
		}
	}
	mini->cmds = cmd_list;
}

int main(int ac, char **av, char **env)
{
    t_mini  mini;
	char	**cmds;

    (void)ac;
    (void)av; 

    mini.env = env_setup(env);
    mini.tokens = NULL;
    mini.cmds = NULL;
    mini.exit_status = 0;

    //print_env(mini.env);

    char    *line;
    while(1)
    {
        line = readline("bbyshell> ");
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (line[0] != '\0')
        {
            add_history(line);
			cmds = ft_split(line, '|');
            print_array(cmds);
			my_cmd_parser(&mini, cmds);
			cmd_handler(mini);
			free(line);
        }
    }
    rl_clear_history();
    return (0);
}
