
#include "../inc/minishell.h"

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