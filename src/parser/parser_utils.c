#include "../../inc/minishell.h"

int     commands_counter(t_token *head)
{
    int count;

    count = 0;
    while (head && head->type != T_PIPE)
    {
        if (head->type == T_WORD)
        {
            count++;
            head = head->next;
        }
        else
        {
            head = head->next;
            if (head)
                head = head->next;
        }
    }
}