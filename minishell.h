#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>          // Per printf, perror
# include <stdlib.h>         // Per malloc, free, exit, getenv
# include <unistd.h>         // Per write, access, read, close, fork, execve, dup, dup2, pipe, getcwd, chdir, isatty, ttyname, ttyslot
# include <string.h>         // Per strerror
# include <fcntl.h>          // Per open
# include <sys/wait.h>       // Per wait, waitpid, wait3, wait4
# include <signal.h>         // Per signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>       // Per stat, lstat, fstat
# include <dirent.h>         // Per opendir, readdir, closedir
# include <sys/ioctl.h>      // Per ioctl
# include <termios.h>        // Per tcsetattr, tcgetattr
# include <curses.h>         // Per alcune funzioni termcap
# include <term.h>           // Per altre funzioni termcap

# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
// Definizioni di prototipi di funzione, se necessario
// ...
# define PROMPT "MINISHELL$>"


typedef enum {
    TOKEN_WORD,         //  o comando o file ??
    TOKEN_PIPE,         //      = |
    TOKEN_REDIR_OUT,     //     = >
    TOKEN_REDIR_IN,    //   m bvhcgcbcbhbjknmlkòl  = <
    TOKEN_REDIR_APPEND, //  = >>
    TOKEN_REDIR_PRE,    //     = <<
    TOKEN_EOF,          // END OF FILE
    TOKEN_AND,
    TOKEN_DOLLAR,
    TOKEN_OPEN_P,
    TOKEN_CLOSE_P,
    TOKEN_DBQUOTE,
    TOKEN_SQUOTE,
    TOKEN_BACKSLASH,
    TOKEN_SPACE,
    TOKEN_DELETE,
	TOKEN_DPIPE,
	TOKEN_DAND,
	TOKEN_PCOMM
    // Aggiungere altri tipi di token necessari
} TokenType;


typedef struct s_token {
    TokenType   type;
    char        *value;
} token;

typedef struct s_cmd {

    char		*cmd;		//command name / path
    t_list  	*args;		//list of arguments
    char    	*inpath;	//file name of INPUT
    char    	*outpath;	//file name of OUTPUT
    char    	**argv;		//arguments matrix (necessary for execve)
    int     	infd;		//input fd
    int     	outfd;		//output fd
	TokenType	inconnect;	//6 possibilities in bash = & | ; && || EOF
	TokenType	outconnect;
}   command;

/*TOKENIZER*/
void    go_next(char **str);
int space_until_next(char   *str);
t_list    *tokenize(char   *str, t_list  **list, char **env);
char	*squote_manager(char *str);
char	*dquote_manager(char *str, char **env);

/*debug*/
void    print_tokens(t_list *list);
void    print_parse(t_list *list);

/*parser*/
t_list	*parser(t_list **tokens,t_list **parsed_list);
char	is_redirection(TokenType type);
char	is_break(t_list *tokens);
char	is_string(TokenType type);
char	is_after_break(t_list *tokens);

/*execute*/
int	str_to_env_index(char **env, char *name);
int     execute(t_list **parsed_list, char **env);
char	*get_path(char **env, char *command);

/*memory*/
void	free_command(void *cmd);
void	free_token(void	*tkn);
void	free_matrix(char **mat);

/*utils*/
char	**listomap(char *cmd,t_list **list);
int		str_to_env_index(char **env, char *name);
int		ft_istokenchar(char c);
char	is_builtin(char *cmd);
void	ft_lst_remove_node(t_list **lst, t_list *node, void (*del)(void *));
int		ft_isspace(char c);

#endif
