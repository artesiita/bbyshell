/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:55:44 by bizcru            #+#    #+#             */
/*   Updated: 2026/03/13 14:50:37 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_exit(t_mini *mini)
{
	mini->exit_status = -1;
	free_everything(mini);
	exit(EXIT_SUCCESS);
	// s'ha de gestionar neteja
}
