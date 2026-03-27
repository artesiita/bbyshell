/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:50:53 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/27 17:03:41 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_arraylen(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	my_echo(t_mini *mini)
{
	int		i;
	int		n_flag;
	char	**argv;

	argv = mini->ex->cur_cmd->args;
	if (!argv || !argv[0] || !argv[1])
	{
		printf("\n");
		return (0);
	}
	i = 0;
	n_flag = 0;
	while (argv[++i] && is_n_flag(argv[i]))
		n_flag = 1;
	while (i < ft_arraylen(argv))
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
