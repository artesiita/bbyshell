
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
	T_REDIR_IN,      /* <  */
	T_REDIR_OUT,     /* >  */
	T_REDIR_HEREDOC, /* << */
	T_REDIR_APPEND   /* >> */
}	t_token_type;

typedef enum e_quote_ctx
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_ctx;

typedef struct s_token
{
	char            *content;
	t_token_type    type;
	t_quote_ctx     quote;
	struct s_token  *next;
}	t_token;

/*============= PARSER ================*/

typedef enum e_redir_type
{
	R_IN,       /* <  */
	R_OUT,      /* >  */
	R_APPEND,   /* >> */
	R_HEREDOC   /* << */
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type    type;
	char            *target;
	struct s_redir  *next;
}	t_redir;

typedef struct s_cmds
{
	char			**args;
	t_redir			*redirs;
	struct s_cmds	*next;
}	t_cmds;

/*============= GLOBAL ================*/

extern volatile sig_atomic_t	g_signal;

typedef struct s_env
{
	char		    *key;
	char		    *value;
	struct s_env    *next;
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

#endif
