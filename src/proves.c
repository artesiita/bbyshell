
#include "../inc/minishell.h"

void print_tokens(t_token *tokens)
{
    t_token *tmp = tokens;

    printf("\n--- TOKEN LIST ---\n");
    while (tmp)
    {
        printf("Content: [%s] | Type: ", tmp->content);
        if (tmp->type == T_WORD) printf("WORD");
        else if (tmp->type == T_PIPE) printf("PIPE");
        else if (tmp->type == T_REDIR_IN) printf("REDIR_IN");
        else if (tmp->type == T_REDIR_OUT) printf("REDIR_OUT");
        else if (tmp->type == T_REDIR_HEREDOC) printf("HEREDOC");
        else if (tmp->type == T_REDIR_APPEND) printf("APPEND");
        
        printf(" | Quote: ");
        if (tmp->quote == Q_NONE) printf("NONE");
        else if (tmp->quote == Q_SINGLE) printf("SINGLE");
        else if (tmp->quote == Q_DOUBLE) printf("DOUBLE");
        
        printf("\n");
        tmp = tmp->next;
    }
    printf("------------------\n\n");
}

void print_cmds(t_cmds *cmds)
{
    int i;
    t_redir *r_tmp;
    int cmd_count = 0;

    printf("\n--- PARSED COMMANDS ---\n");
    while (cmds)
    {
        printf("COMMAND [%d]:\n", cmd_count++);
        
        // Print Arguments
        printf("  Args: ");
        if (cmds->args)
        {
            for (i = 0; cmds->args[i]; i++)
                printf("[%s] ", cmds->args[i]);
        }
        else
            printf("(NULL)");
        printf("\n");

        // Print Redirections
        printf("  Redirs: ");
        r_tmp = cmds->redirs;
        if (!r_tmp)
            printf("(NONE)");
        while (r_tmp)
        {
            printf("[%d -> %s] ", r_tmp->type, r_tmp->target);
            r_tmp = r_tmp->next;
        }
        printf("\n-----------------------\n");
        cmds = cmds->next;
    }
}