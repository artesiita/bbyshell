/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:54:35 by bizcru            #+#    #+#             */
/*   Updated: 2026/02/22 19:38:37 by lartes-s         ###   ########.fr       */
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

	printf("Aquí executem el builtin de my_export, he rebut %s\n",
		data->args[0]);
	if (!data->args[1])
	{
		new_env = env_cpy(data->mini->env);
		sort_env(new_env);
		print_export(new_env);
	}
	return (0);
}
