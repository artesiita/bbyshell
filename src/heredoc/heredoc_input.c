/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:01:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/19 20:03:56 by lartes-s         ###   ########.fr       */
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

	while (hd)
	{
		i = 0;
		while (hd->line[i])
		{
			if ((hd->line[i] == '$' && hd->line[i + 1])
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

int	heredoc_input(t_mini *mini)
{
	int	quoted;
	t_token	*cur;

	cur = mini->tokens;
	while (cur)
	{
		if (cur->type == T_REDIR_HEREDOC)
		{
			if (!cur->next || cur->next->type != T_WORD)
			{
				printf("Bbyshell: syntax error near unexpected token `newline'\n");
				mini->exit_status = 2;
				return (ERROR);
			}
			quoted = is_quoted(cur->next->content);
			if (quoted == 1)
				cur->next->content = remove_quotes(cur->next->content);
			fill_heredoc(&cur->hd, cur->next->content);
			if (quoted == 0)
				expand_lines(mini, cur->hd);
		}
		cur = cur->next;
	}
	return (SUCCESS);
}
