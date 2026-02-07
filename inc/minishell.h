
#ifndef MINISHELL_H
# define MINISHELL_H

/*-----------------------------------------------------------------*/
/*                             INCLUDES                            */
/*-----------------------------------------------------------------*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

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
}	t_token_type;

typedef enum e_quote_ctx
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_ctx;

typedef struct s_token
{
	struct s_token  *next;
	char            *content;
	t_token_type    type;
	t_quote_ctx     quote;
}	t_token;

/*============= PARSER ================*/

typedef enum e_redir_type
{
	R_IN = 10,       /* <  */
	R_OUT = 11,      /* >  */
	R_APPEND = 12,   /* >> */
	R_HEREDOC = 13   /* << */
}	t_redir_type;

typedef struct s_redir
{
	struct s_redir  *next;
	t_redir_type    type;
	char            *target;
}	t_redir;

typedef struct s_cmds
{
	struct s_cmds	*next;
	char			**args;
	t_redir			*redirs;
}	t_cmds;

/*============= EXECUTOR ===============*/
typedef struct s_cmd_ex
{
	char	*path;
	char	**args;
	int		fd_in;
	int		fd_out;
}	t_cmd_ex;

typedef struct s_executor
{
	char	**env;
	t_cmds	*cmds;
	pid_t	*childs;
	int		fds[2][2];
}	t_executor;

/*============= GLOBAL ================*/

extern volatile sig_atomic_t	g_signal;

typedef struct s_env
{
	struct s_env    *next;
	char		    *key;
	char		    *value;
}	t_env;

typedef struct s_mini
{
	t_env   *env;
	int		exit_status;
	t_token *tokens;
	t_cmds  *cmds;
}	t_mini;

/*-----------------------------------------------------------------*/
/*                           PROTOTYPES                            */
/*-----------------------------------------------------------------*/

/*============= ENV ================*/
t_env   *env_setup(char **env);
void	free_env_list(t_env *head);

/*============= LEXER ================*/
int		is_redirection(char c);
int		is_space(char c);
void    add_token(t_token **head, char *content, t_token_type type, t_quote_ctx quote);
void	free_token_list(t_token *head);
t_token *lexer(char *input);

/*============ EXECUTOR ==============*/
void	cmd_handler(t_mini *mini);
t_cmd_ex	*load_data(char **cmd, char **env, int fd_in, int fd_out);
void	open_files(char *file_in, char *file_out, int *filefds);
void	my_close(int fd1, int fd2, char *msg);
void	clean(t_cmd_ex *data);
void	clean_exit(t_cmd_ex *data, int my_errno, char *msg);
void	handle_err(int my_errno, char *msg);
void	redirect(t_cmd_ex *data);
void	close_exit(int *fds, int my_errno, char *msg);
void	free_close_exit(int *fds1, int *fds2, pid_t *childs, char *msg);
void	wait_childs(pid_t *childs);

#endif
