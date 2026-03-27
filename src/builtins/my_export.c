/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:54:35 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/27 17:58:42 by becanals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_export(t_env *env)
{
	t_env	*cur;

	if (!env)
		return ;
	cur = env;
	while (cur)
	{
		printf("declare -x %s", cur->key);
		if (cur->value)
			printf("=\"%s\"", cur->value);
		printf("\n");
		cur = cur->next;
	}
}

int	export_value(t_mini *mini, char **ag, char *limit, char *key)
{
	int		i;
	char	*value;

	i = 0;
	while (ag[++i])
	{
		if (!ft_isalpha(ag[i][0]))
		{
			printf("bbyshell: export: %s : not a valid identifier\n", ag[i]);
			return (ERROR);
		}
		value = NULL;
		limit = (char *)ft_strchr(ag[i], '=');
		key = ft_substr(ag[i], 0, limit - ag[i]);
		if (limit)
			value = ft_strdup(limit + 1);
		if (check_env_variable(mini->env_head, key))
			update_env_value(mini->env_head, key, value);
		else
			append_env_node(&mini->env_head, &mini->env_cur, ag[i]);
		free(key);
		free(value);
	}
	return (0);
}

int	my_export(t_mini *mini)
{
	t_env	*new_env;
	char	*limit;
	char	*key;

	if (!mini->ex->cur_cmd->args[1])
	{
		new_env = env_cpy(mini->env_head);
		sort_env(new_env);
		print_export(new_env);
		free_env(new_env);
	}
	limit = NULL;
	key = NULL;
	export_value(mini, mini->ex->cur_cmd->args, limit, key);
	return (0);
}
