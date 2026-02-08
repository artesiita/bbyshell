#include "../../inc/minishell.h"

int is_space(char c)
{
    if (c == ' ')
        return (1);
    return (0);
}

int is_redirection(char c)
{
    if (c == '<' || c == '>' || c == '|')
        return (1);
    return (0);
}

void    add_token(t_token **head, char *content, t_token_type type, t_quote_ctx quote)
{
    t_token *new;
    t_token *last;

    new = malloc(sizeof(t_token));
    if (!new)
        return;
    new->content = content;
    new->type = type;
    new->quote = quote;
    new->next = NULL;
    if (*head == NULL)
        *head = new;
    else
    {
        last = *head;
        while (last->next != NULL)
            last = last->next;
        last->next = new;
    }
}