/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:33:44 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:40:16 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "src/builtin/builtin.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# define PROMPT "MINISHELL$>"

typedef enum s_Tokentype
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_PRE,
	TOKEN_EOF,
}	t_TokenType;

typedef struct s_token
{
	t_TokenType	type;
	char		*value;
}	t_token;

typedef struct s_cmd
{
	char		*cmd;
	t_list		*args;
	char		*inpath;
	char		*outpath;
	char		**argv;
	int			infd;
	int			outfd;
	t_TokenType	inconnect;
	t_TokenType	outconnect;
}	t_command;

extern int	g_status;

/*TOKENIZER*/
int			space_until_next(char *str);
t_list		*tokenize(char *str, t_list **list);
int			ft_istokenquotes(char c);
int			append_token(char **str, t_list **lst);

/*EXPANDER*/
t_list		*expand(t_list **list, char **env);
char		*expand_token_value(const char *value);
char		*expand_token(char *str, char **env);
char		*ft_strjoin_char(char *s1, char c);
char		*expand_var(char *var, char **env);
int			var_len(char *var);
char		*remove_quotes(char *str);
char		*expand_token(char *str, char **env);

/*debug*/
void		print_tokens(t_list *list);
void		print_parse(t_list *list);

/*parser*/
int			append_cmd(t_list	**tokens, t_list **parsed_list);
t_TokenType	get_command_inconnect(t_list **tokens, int isfirst);
char		is_redirection(t_TokenType type);
char		is_break(t_list *tokens);
char		is_string(t_TokenType type);
char		is_after_break(t_list *tokens);

/*execute*/
int			exec_builtin(char *cmd, char **argv, char ***env, int *ret);
int			execute(t_list **parsed_list, char ***env);
int			heredoc(t_command *command, char **env);
int			pipes(t_list **lst);
int			access_or_create(char *path);

/*memory*/
void		free_command(void *cmd);
void		free_token(void *tkn);
void		free_matrix(char **mat);

/*utils*/
int			blank_check(char *str);
char		**ft_matdup(char **mat);
char		*get_env(char **env, char *name);
char		**listomap(char *cmd, t_list *list);
int			str_to_env_index(char **env, char *name);
int			ft_istokenchar(char c);
char		is_builtin(char *cmd);
void		ft_lst_remove_node(t_list **lst, t_list *node, void (*del)(void *));
int			ft_isspace(char c);
int			ft_contains_dollar(const char *str);
void		close_fds(t_list *lst);

/*signals*/
void		ft_signals(void);
void		handlec_heredoc(int sig);

#endif
