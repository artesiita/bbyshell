/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laiaartes <laiaartes@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:38:57 by lartes-s          #+#    #+#             */
/*   Updated: 2026/04/13 19:48:00 by laiaartes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*-----------------------------------------------------------------*/
/*                             INCLUDES                            */
/*-----------------------------------------------------------------*/

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "\033[1;35mbbyshell\033[35m> \033[0m"
# define ERROR 1
# define SUCCESS 0

# define NEW_FDS 0
# define OLD_FDS 1

# define P_READ 0
# define P_WRITE 1

/*-----------------------------------------------------------------*/
/*                             STRUCTS                             */
/*-----------------------------------------------------------------*/

/*============= LEXER ================*/

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN = 10,/* <  */
	T_REDIR_OUT = 11,/* >  */
	T_REDIR_HEREDOC = 12,/* << */
	T_REDIR_APPEND = 13/* >> */
}								t_token_type;

typedef struct s_token
{
	struct s_token	*next;
	char			*content;
	t_token_type	type;
}					t_token;

/*============= PARSER ================*/

typedef enum e_redir_type
{
	R_IN = 10,/* <  */
	R_OUT = 11,/* >  */
	R_HEREDOC = 12,/* << */
	R_APPEND = 13 /* >> */
}								t_redir_type;

typedef struct s_expan
{
	char	*pre;
	char	*val;
	char	*suf;
	char	*tmp;
	char	*res;
	char	*key;
}			t_expan;

typedef struct s_redir
{
	struct s_redir	*next;
	t_redir_type	type;
	char			*target;
}					t_redir;

typedef struct s_cmds
{
	struct s_cmds	*next;
	char			**args;
	t_redir			*redirs;
}					t_cmds;

/*============= EXECUTOR ===============*/

typedef struct s_hd_data
{
	struct s_hd_data			*next;
	char						*line;
}								t_hd_data;

typedef struct s_hedoc
{
	struct s_hedoc				*next;
	int							fd;
	t_hd_data					*data;
}								t_hedoc;

typedef struct s_executor
{
	pid_t						*childs;
	int							fds[2][2];
	t_cmds						*cur_cmd;
	t_hedoc						*hedocs;
}								t_executor;

/*============= GLOBAL ================*/

typedef struct s_env
{
	struct s_env				*next;
	char						*key;
	char						*value;
}								t_env;

typedef struct s_mini
{
	t_env						*env_head;
	t_env						*env_cur;
	int							exit_status;
	t_token						*tokens;
	t_cmds						*cmds;
	t_executor					*ex;
}	t_mini;

/*-----------------------------------------------------------------*/
/*                           PROTOTYPES                            */
/*-----------------------------------------------------------------*/

/*============= ENV ================*/
int		env_setup(t_mini *mini, char **env);
void	free_env_list(t_env *head);
char	*get_env_value(char *key, t_env *env);
void	update_env_value(t_env *env, char *key,	char *new_value);
char	*get_env_dup(char *key, t_env *env);

/*============= LEXER ================*/
int		is_redirection(char c);
int		is_space(char c);
void	add_token(t_token **head, char *content, t_token_type type);
t_token	*lexer(t_mini *mini, char *input);

/*============= EXPANSIONS ================*/
int		expansions(t_mini *mini);
void	filter_expansion(t_mini *mini, t_token *tok, int i);
void	expand_double_quoted(t_mini *mini, t_token *token);
char	*expand_to_str(t_mini *mini, char *str, int *dollar_idx, int i);
void	expand_to_tokens(t_mini *mini, t_token *token, int *dollar_idx, int i);

/*============= PARSER ================*/
t_cmds	*parsing(t_mini *mini);
int		commands_counter(t_token *head);
void	add_command_node(t_cmds **head, t_cmds *new_node);

/*============ EXECUTOR ==============*/
void	ft_executor(t_mini *mini);
void	ft_redir_in(t_mini *mini, t_redir *redir);
void	ft_redir_out(t_mini *mini, t_redir *redir);
void	ft_redir_heredoc(t_mini *mini, t_redir *redir);
void	ft_redir_append(t_mini *mini, t_redir *redir);
void	set_heredoc(t_mini *mini, char *end);
void	dump_heredoc(t_mini *mini);
void	open_files(char *file_in, char *file_out, int *filefds);
void	my_close(int *fd1, int *fd2, char *msg);
int		redirect(t_mini *mini);
void	wait_childs(pid_t *childs);
int		my_execve(t_mini *mini);
int		(*get_builtin_ft(t_mini *mini))(t_mini *);
void	ft_postex_clean(t_mini *mini);

/*============ BUILT-INS ==============*/
int		my_echo(t_mini *mini);
int		my_cd(t_mini *mini);
int		my_pwd(t_mini *mini);
int		my_export(t_mini *mini);
int		my_unset(t_mini *mini);
int		my_env(t_mini *mini);
int		my_exit(t_mini *mini);
t_env	*create_node(t_mini *mini, char *key, char *value);
void	sort_env(t_env *head);
t_env	*env_cpy(t_mini *mini, t_env *head);
int		append_env_node(t_mini *mini, t_env **head, t_env **cur, char *content);
int		check_env_variable(t_env *head, char *key);

/*============= CLEANUP ================*/
void	fatal_error(t_mini *mini, char *msg, int status);
void	free_everything(t_mini *mini);
void	free_tokens(t_token *head);
void	free_env(t_env *env);
void	free_commands(t_cmds *cmds);
void	free_redirs(t_redir *redirs);
void	free_str_array(char **array);
void	free_parsing(t_mini *mini);

/*============= PROVES ================*/
void	print_cmds(t_cmds *cmds);
void	print_tokens(t_token *tokens);
void	print_env(t_env *env);
void	signals_nonintmode(void);
void	signals_intmode(void);
void rl_replace_line(const char *text, int clear_undo);

#endif
