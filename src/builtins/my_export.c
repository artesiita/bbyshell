/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:54:35 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/07 18:06:32 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_export(t_env *env)
{
	t_env	*cur;

	if (!env)
		return ;
	cur = env;
	while (cur->next)
	{
		printf("declare -x %s", cur->key);
		if (cur->value)
			printf("=\"%s\"\n", env->value);
		cur = cur->next;
	}
}

int	my_export(t_mini *mini)
{
	t_env	*new_env;
	int		i;

	i = 1;
	// printf("CUR NODE: %s=%s\n", mini->env_cur->key, mini->env_cur->value);
	if (!mini->ex->cur_cmd->args[i])
	{
		new_env = env_cpy(mini->env_head);
		sort_env(new_env);
		print_export(new_env);
		free_env(&new_env);
	}
	while (mini->ex->cur_cmd->args[i])
	{
		if (!ft_isalpha(mini->ex->cur_cmd->args[i][0]))
			printf("bbyshell: export: %s : not a valid identifier\n",
				mini->ex->cur_cmd->args[i]);
		else
		{
			// printf("hauria d'afegir %s\n", mini->ex->cur_cmd->args[i]);
			append_env_node(&mini->env_head, &mini->env_cur,
				mini->ex->cur_cmd->args[i]);
			// printf("CUR NODE: %s=%s\n", mini->env_cur->key,
			// mini->env_cur->value);
		}
		i++;
	}
	return (0);
}
