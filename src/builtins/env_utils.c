
#include "../../inc/minishell.h"

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

/*
t_env	*create_env_node(char *content)
{
	t_env   *new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
}*/