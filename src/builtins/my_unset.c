/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:02 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/07 18:12:35 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_unset(t_mini *mini)
{
	printf("Aquí executem el builtin de my_unset, he rebut %s\n",
		mini->ex->cur_cmd->args[0]);
	return (0);
}
