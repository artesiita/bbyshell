/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:01:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/25 19:12:10 by lartes-s         ###   ########.fr       */
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
void	print_closed_hd_msg(t_heredoc **hd, char *end)
{
	char *lines;

	lines = ft_itoa(ft_lstcount(*hd) + 1);
	write(2, "minishell: warning: here-document at line ", 42);
	write(2, lines, ft_strlen(lines));
	write(2, " delimited by end-of-file (wanted '", 35);
	write(2, end, ft_strlen(end));
	write(2, "')\n", 3);
}


int	fill_heredoc(t_heredoc **hd, char *end)
{
	char	*line;
	void	*new;
	int		exit_from_signal;

	exit_from_signal = 0;
	line = readline("> ");
	while (!ft_streq(line, end))
	{
		if (check_signal_interrupt(line, &exit_from_signal))
			break ;
		if (!line)
			return (print_closed_hd_msg(hd, end), exit_from_signal);
		new = ft_lstnew(sizeof(t_heredoc), line);
		if (!new)
			return exit_from_signal;
		ft_lstadd_back((void **)hd, new);
		line = readline("> ");
	}
	return (exit_from_signal);
}

int	heredoc_input(t_mini *mini)
{
	int		quoted;
	t_token	*cur;
	int		exit_from_signal;

	cur = mini->tokens;
	while (cur)
	{
		if (cur->type == T_REDIR_HEREDOC)
		{
			quoted = is_quoted(cur->next->content);
			setup_heresignals(&exit_from_signal);
			if (quoted == 1)
				cur->next->content = remove_quotes(cur->next->content);
			fill_heredoc(&cur->hd, cur->next->content);
			if (cur->hd && quoted == 0)
				expand_lines(mini, cur->hd);
		}
		cur = cur->next;
	}
	return (exit_from_signal);
}
