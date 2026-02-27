/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:54:35 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/27 19:30:15 by lartes-s         ###   ########.fr       */
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

int	my_export(t_cmd_ex *data)
{
	t_env	*new_env;
	int		i;

	// t_env	*head;
	// t_env	*cur;
	i = 1;
	printf("CUR NODE: %s=%s\n", data->mini->env_cur->key,
		data->mini->env_cur->value);
	// head = data->mini->env_head;
	// cur = data->mini->env_cur;
	if (!data->args[i])
	{
		new_env = env_cpy(data->mini->env_head);
		sort_env(new_env);
		print_export(new_env);
	}
	while (data->args[i])
	{
		if (!ft_isalpha(data->args[i][0]))
			printf("bbyshell: export: %s : not a valid identifier\n",
				data->args[i]);
		else
		{
			printf("hauria d'afegir %s\n", data->args[i]);
			append_env_node(&data->mini->env_head, &data->mini->env_cur,
				data->args[i]);
			// data->mini->env_head = head;
			// data->mini->env_cur = cur;
			printf("CUR NODE: %s=%s\n", data->mini->env_cur->key,
				data->mini->env_cur->value);
		}
		i++;
	}
	return (0);
}

// ERROR NOM---> bash: export: `2laia': not a valid identifier