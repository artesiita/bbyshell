
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
	T_REDIR_IN = 10,      /* <  */
	T_REDIR_OUT = 11,     /* >  */
	T_REDIR_HEREDOC = 12, /* << */
	T_REDIR_APPEND = 13   /* >> */
}								t_token_type;

typedef enum e_quote_ctx
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}								t_quote_ctx;

typedef struct s_token
{
	struct s_token				*next;
	char						*content;
	t_token_type				type;
	t_quote_ctx					quote;
}								t_token;

/*============= PARSER ================*/

typedef enum e_redir_type
{
	R_IN = 10,     /* <  */
	R_OUT = 11,    /* >  */
	R_APPEND = 12, /* >> */
	R_HEREDOC = 13 /* << */
}								t_redir_type;

typedef struct s_redir
{
	struct s_redir				*next;
	t_redir_type				type;
	char						*target;
}								t_redir;

typedef struct s_cmds
{
	struct s_cmds				*next;
	char						**args;
	t_redir						*redirs;
}								t_cmds;

/*============= EXECUTOR ===============*/

typedef struct s_executor
{
	// Ja hi ha una funció que retorna el valor de una variable de dins de env.
	// Es diu "get_env_value", a la branca de built-in
	pid_t						*childs;
	int							fds[2][2];
	t_cmds						*cur_cmd;
}								t_executor;

/*============= GLOBAL ================*/

extern volatile sig_atomic_t	g_signal;

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
}								t_mini;

/*-----------------------------------------------------------------*/
/*                           PROTOTYPES                            */
/*-----------------------------------------------------------------*/

/*============= ENV ================*/
int								env_setup(t_mini *mini, char **env);
void							free_env_list(t_env *head);
char							*get_env_value(char *key, t_env *env);
void		update_env_value(char *key, t_env *env, char *new_value);

/*============= LEXER ================*/
int								is_redirection(char c);
int								is_space(char c);
void							add_token(t_token **head, char *content,
									t_token_type type, t_quote_ctx quote);
t_token							*lexer(char *input);

/*============= PARSER ================*/
t_cmds							*parsing(t_mini *mini);
int								commands_counter(t_token *head);
void							add_command_node(t_cmds **head,
									t_cmds *new_node);

/*============ EXECUTOR ==============*/
void							ft_executor(t_mini *mini);
void							open_files(char *file_in, char *file_out,
									int *filefds);
void							my_close(int fd1, int fd2, char *msg);
int								redirect(t_mini *mini);
int								my_execve(t_mini *mini);

/*============ BUILT-INS ==============*/
int								my_echo(t_mini *mini);
int								my_cd(t_mini *mini);
int								my_pwd(t_mini *mini);
int								my_export(t_mini *mini);
int								my_unset(t_mini *mini);
int								my_env(t_mini *mini);
int								my_exit(t_mini *mini);
t_env							*create_node(char *key, char *value);
void							sort_env(t_env *head);
t_env							*env_cpy(t_env *head);
int								append_env_node(t_env **head, t_env **cur,
									char *content);

/*============= CLEANUP ================*/
void							fatal_error(t_mini *mini, char *msg,
									int status);
void							free_everything(t_mini *mini);
void							free_tokens(t_token **head);
void							free_env(t_env **env);
void							free_commands(t_cmds **cmds);
void							free_redirs(t_redir **redirs);
void							free_str_array(char **array);

/*============= PROVES ================*/
void							print_cmds(t_cmds *cmds);
void							print_tokens(t_token *tokens);
void							print_env(t_env *env);

#endif
