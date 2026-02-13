#include "../../inc/minishell.h"

void	free_str_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_redirs(t_redir **redirs)
{
	t_redir	*tmp;

	if (!redirs || !*redirs)
		return ;
	while (*redirs)
	{
		tmp = (*redirs)->next;
		free((*redirs)->target);
		free(*redirs);
		*redirs = tmp;
	}
}

void	free_commands(t_cmds **cmds)
{
	t_cmds	*tmp;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		tmp = (*cmds)->next;
		free_str_array((*cmds)->args);
		if ((*cmds)->redirs)
			free_redirs(&(*cmds)->redirs);
		free(*cmds);
		*cmds = tmp;
	}
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}

void	free_tokens(t_token **head)
{
	t_token *temp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		if ((*head)->content)
			free((*head)->content);
		free(*head);
		*head = temp;
	}
}