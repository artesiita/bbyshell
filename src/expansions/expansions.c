
#include "../../inc/minishell.h"

void    expand_variable(char *str, int start)
{
    int     end;
    char    *var;
    int     var_len;
    int     i;

    start++;
    if (str[start] == ' ')
        return ;
    end = start;
    while (str[end] != ' ' ||  str[end] != '\0')
        end++;
    var_len = end - start;
    var = malloc(sizeof(char) * var_len + 1);
    if (!var)
    {
        //gestionar malloc error
    }
    i = 0;
    while (var[i])
    {
        var[i] = str[start + i];
        i++;
    }

}

void    expand_content(t_token *token)
{
    int i;

    i = 0;
    while (token->content[i])
    {
        if (token->content[i] == '$')
        {
            if (token->content[i + 1] == '?')
                expand_last_error(token->content);
            else
                expand_variable(token->content, i);
        }
        i++;
    }
}

int     expansions(t_mini *mini)
{
    t_token     *cur;
    int         i;

    cur = mini->tokens;
    if (!cur)
        return (ERROR);
    while (cur)
    {
        if (cur->type != Q_SINGLE)
            expand_content(cur);
        cur = cur->next;
    }
    return (0);
}