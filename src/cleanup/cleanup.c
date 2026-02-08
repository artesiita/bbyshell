#include "../../inc/minishell.h"

void    free_everything(t_mini *mini)
{
    free_env(&mini->env);
    free_tokens(&mini->tokens);
    free_commands(&mini->cmds);
}

void    fatal_error(t_mini *mini, char *msg, int status)
{
    if (msg)
        perror(msg);
    free_everything(mini);
    exit(status);
}