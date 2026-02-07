#include "../../inc/minishell.h"

void    parse_redirection(t_cmds *node, t_token *cur)
{
    t_redir *redir;
    t_redir *tmp;

    redir = ft_calloc(1, sizeof(t_redir));
    if (!redir)
        /*MALLOC ERROR: need to think how to handle*/
    redir->type = (t_redir_type)cur->type;
    redir->target = ft_strdup(cur->next->content);
    redir->next = NULL;
    if (node->redirs == NULL)
        node->redirs = redir;
    else
    {
        tmp = node->redirs;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = redir;
    }
}

void    fill_args(t_cmds *node, t_token *cur)
{
    int i;

    i = 0;
    while (cur && cur->type != T_PIPE)
    {
        if (cur->type == T_WORD)
        {
            node->args[i] = ft_strdup(cur->content);
            i++;
            cur = cur->next;
        }
        else
        {
            parse_redirection(node, cur);
            cur = cur->next;
            if (cur)
                cur = cur->next;
        }
    }
}

t_cmds  *parsing(t_mini *mini)
{
    t_token *cur;
    t_cmds  *head;
    t_cmds  *new_node;

    cur = mini->tokens;
    head = NULL;
    if (cur && cur->type == T_PIPE)
    {
        /*SYNTAX ERROR: a pipe can't be the first command
            need to think how to handle this*/
    }
    while(cur)
    {
        new_node = ft_calloc(1, sizeof(t_cmds));
        if (!new_node)
        /*MALLOC ERROR: need to think how to handle*/
        new_node->args = ft_calloc(commands_counter(cur), sizeof(char *));
        fill_args(new_node, cur);
        add_command_node(&head, new_node);
        while(cur && cur->type != T_PIPE)
            cur = cur->next;
        if (cur && cur->type == T_PIPE)
        {
            if (!cur->next || cur->next == T_PIPE)
                /*SYNTAX ERROR: pipe at the end of the command line
                or consecutive pipes. Need to think how to handle*/
            cur = cur->next;
        }
    }
    return (head);
}
