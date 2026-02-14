#include "../../inc/minishell.h"

int	ft_env(t_mini *mini, char **av)
{
	t_env	*current;

	current = mini->env;
	if (!mini->env || !mini->env->key || !mini->env->value)
		return (1);
	if (av[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(av[1], STDERR_FILENO);
		ft_putstr_fd("command not found", STDERR_FILENO);
	}
	while (current)
	{
		if (current->value)
		{
			printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
	return (0);
}