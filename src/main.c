
#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
    t_mini  mini;

    (void)ac;
    (void)av; 

    mini.env = env_setup(env);
    mini.tokens = NULL;
    mini.pipeline = NULL;
    mini.exit_status = 0;

    print_env(mini.env);

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
            mini.tokens = lexer(line);
            if (mini.tokens)
            {
                print_tokens(mini.tokens);
                free_token_list(mini.tokens);
                mini.tokens = NULL;
            }
            free(line);
        }
    }
    rl_clear_history();
    return (0);
}
