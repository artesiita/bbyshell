/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:01:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/19 18:49:27 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		is_quoted(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}


void	expand_lines(t_mini *mini, t_heredoc *hd)
{
	char	*old;
	int			i;

	i = 0;
	while (hd->line)
	{
		while (hd->line[i])
		{
			if (hd->line[i] == '$' && hd->line[i + 1]
				&& (ft_isalnum(hd->line[i + 1]) || hd->line[i + 1] == '_'
					|| hd->line[i + 1] == '?'))
			{

				old = hd->line;
				hd->line = expand_to_str(mini, hd->line, &i, i + 1);
				free(old);
			}
			else
				i++;
		}
		hd = hd->next;
	}
}

void	fill_heredoc(t_heredoc **hd, char *end)
{
	char	*line;
	void	*new;

	line = readline("> ");
	while (!ft_streq(line, end))
	{
		new = ft_lstnew(sizeof(t_heredoc), line);
		if (!new)
			return ;
		ft_lstadd_back((void **)hd, new);
		line = readline("> ");
	}
}

void	heredoc_input(t_mini *mini)
{
	int	quoted;

	while (mini->tokens)
	{
		if (mini->tokens->type == T_REDIR_HEREDOC)
		{
			quoted = is_quoted(mini->tokens->next->content);
			fill_heredoc(&mini->tokens->hd, mini->tokens->next->content);
			if (quoted == 0)
				expand_lines(mini, mini->tokens->hd);
		}
		mini->tokens = mini->tokens->next;
	}
}