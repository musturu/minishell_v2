#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>     // Per printf, perror
#include <stdlib.h>    // Per malloc, free, exit, getenv
#include <unistd.h>    // Per write, access, read, close, fork, execve, dup, dup2, pipe, getcwd, chdir, isatty, ttyname, ttyslot
#include <string.h>    // Per strerror
#include <fcntl.h>     // Per open
#include <sys/wait.h>  // Per wait, waitpid, wait3, wait4
#include <signal.h>    // Per signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/stat.h>  // Per stat, lstat, fstat
#include <dirent.h>    // Per opendir, readdir, closedir
#include <sys/ioctl.h> // Per ioctl
#include <termios.h>   // Per tcsetattr, tcgetattr

#include "src/builtin/builtin.h"

#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
// Definizioni di prototipi di funzione, se necessario
// ...
#define PROMPT "MINISHELL$>"
#define NEEDFORK(arg) is_builtin(arg) != 1

typedef enum
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_APPEND,
    TOKEN_REDIR_PRE,
    TOKEN_EOF,
} e_TokenType;

typedef struct s_token
{
    e_TokenType type;
    char *value;
} t_token;

typedef struct s_cmd
{
    char *cmd;           // command name / path
    t_list *args;        // list of arguments
    char *inpath;        // file name of INPUT
    char *outpath;       // file name of OUTPUT
    char **argv;         // arguments matrix (necessary for execve)
    int infd;            // input fd
    int outfd;           // output fd
    e_TokenType inconnect; // 6 possibilities in bash = & | ; && || EOF
    e_TokenType outconnect;
} t_command;

extern int status;

/*TOKENIZER*/
int space_until_next(char *str);
t_list *tokenize(char *str, t_list **list);
int	ft_istokenquotes(char c);
int	append_token(char **str, t_list **lst);

/*EXPANDER*/
t_list *expand(t_list **list);
char *expand_token_value(const char *value);

/*debug*/
void print_tokens(t_list *list);
void print_parse(t_list *list);

/*parser*/
int	append_cmd(t_list	**tokens, t_list **parsed_list);
e_TokenType get_command_inconnect(t_list **tokens, int isfirst);
char is_redirection(e_TokenType type);
char is_break(t_list *tokens);
char is_string(e_TokenType type);
char is_after_break(t_list *tokens);

/*execute*/
int exec_builtin(char *cmd, char **argv, char ***env, int *ret);
int execute(t_list **parsed_list, char ***env);
int	heredoc(t_command *command, char **env);
int	pipes(t_list **lst);

/*memory*/
void free_command(void *cmd);
void free_token(void *tkn);
void free_matrix(char **mat);

/*utils*/
int blank_check(char *str);
char    **ft_matdup(char **mat);
char	*get_env(char **env, char *name);
char **listomap(char *cmd, t_list *list);
int str_to_env_index(char **env, char *name);
int ft_istokenchar(char c);
char is_builtin(char *cmd);
void ft_lst_remove_node(t_list **lst, t_list *node, void (*del)(void *));
int ft_isspace(char c);
int ft_contains_dollar(const char *str);
void	close_fds(t_list *lst);

/*signals*/
void	ft_signals(void);
void	handlec_heredoc(int sig);

#endif
