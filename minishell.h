/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:55:09 by zjaddad           #+#    #+#             */
/*   Updated: 2023/06/04 16:50:04 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing/GNL/get_next_line.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

# define STDRIN 0
# define STDROUT 1
# define STDRERR 2
# define PIPE_END -42

# define CD 1
# define PWD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6
# define ECHO 7
# define NONE_BLT 0

//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 							Struct :: tocken 							!//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum s_tokens_type
{
	t_CHAR,
	t_PIPE,
	t_GREAT_THAN,
	t_LESS_THAN,
	t_HEREDOC,
	t_APPEND,
	t_EOF,
}						t_tokens_type;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_tokens
{
	t_tokens_type		type;
	char				*val;
}						t_token;
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 							Struct :: lexer 							!//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct s_lexer
{
	char				*src;
	char				c;
	unsigned int		i;
	size_t				len_src;
	int					ex_status;
	t_env				*env;
}						t_lexer;

typedef struct cmd
{
	char				*value;
	struct cmd			*next;
}						t_cmd;

typedef struct parser_struct
{
	t_lexer				*lexer;
	t_token				*current_token;
	t_token				*previous_token;
}						t_parser;

typedef struct s_gob
{
	int					ex_status;
	int					ex;
	int					to_expand;
	int					nb_cmds;
	int					nb_err;
	int					ambg_redir;
	int					p_chld;
	t_env				*env_p;
	t_env				*exprt;
	int					fd_here_doc;
}						t_gob;

typedef struct s_exc
{
	int					bltns;
	int					child_pro;
	int					i;
}						t_exc;

typedef struct t_args
{
	char				*args;
	struct t_args		*next;
}						t_args;
typedef struct s_here_doc
{
	char				*delim;
	struct s_here_doc	*next;
}						t_here_doc;

typedef struct s_data_cmd
{
	t_args				*args;
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	struct s_data_cmd	*next;
}						t_data_cmd;
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 					Struct  :: the envirment variable					!//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//!+++++++++++++++++++++++++++lexer functions+++++++++++++++++++++++++++!//
// function to initialize the tokens
t_token					*init_tokens(t_tokens_type typ, char *val);
t_lexer					*init_lexer(char *str);
void					advance_lexer(t_lexer *lexer);
void					lexer_skip_whitespace(t_lexer *lexer);
t_token					*get_next_token(t_lexer *lexer, int flag);
t_token					*lexer_advance_with_token(t_lexer *lexer,
							t_token *token);
t_token					*advance_to_next_tocken(t_lexer *lexer, t_token *token);
char					*exit_value(t_lexer *lexer);
char					*single_quote(t_lexer *lexer);
char					*envairment_var(t_lexer *lexer);
void					expand_dollar(t_lexer *lexer, char **my_str);
void					get_string_between_double_qoutes(t_lexer *lexer,
							char **my_str, int flag);
char					*double_quote(t_lexer *lexer, int flag);
char					*hundle_quotes(t_lexer *lexer, int flag);
void					error_func(int err);
char					*get_dollar(t_lexer *lexer, int flag);
char					*get_envairment_var(char *to_find);
char					*get_char(t_lexer *lexer, int flag);
char					*remove_multiple_spaces(char *s);
void					get_env(char **envp);
int						check_qutes(t_lexer *lexer, char q);
t_token					*rederection_less(t_lexer *lexer);
t_token					*rederection_great(t_lexer *lexer);
//!+++++++++++++++++++++++++++parsing functions+++++++++++++++++++++++++++!//
t_parser				*initialize_parser(char *input);
int						max_heredoc(char *str);
int						start_parsing(t_parser *parser, t_data_cmd **cmd);
void					iterate_over_tokens_check_syntaxe(t_parser *parser);
int						err_msg(char *msg);
int						type_is_char(t_token *token);
int						type_is_rederec(t_token *token);
int						type_is_pipe(t_token *token);
int						type_out_in(t_token *token);
int						type_hd_apd(t_token *token);
void					reinitialize_parser(t_parser *parser);
int						err_msg_ii(char *msg);
//! +++++++++++++++++++++++++++ linked list functions +++++++++++++++++++++++++
t_data_cmd				*ft_new_cmd(t_args *arg, int fd_in, int fd_out);
void					ft_add_back_cmd(t_data_cmd **head, t_data_cmd *new);
t_args					*ft_new_arg(char *arg);
void					ft_add_back_arg(t_args **head, t_args *new);
//!+++++++++++++++++++++++++Dividing cmd+++++++++++++++++++++++++++++++++++++
t_args					*create_node(t_parser *parser, int *fd_in, int *fd_out);
int						divid_cmd(t_parser *parser, t_data_cmd **cmd_data);
int						out_file(char *file_name, int *fd_out);
int						in_file(char *file_name, int *fd_out);
int						append_file(char *file_name, int *fd_out);
//!+++++++++++++++++++++++++++++++files++++++++++++++++++++++++++++++++
char					*generate_filename(void);
//!\************************************************************************* */
//!									FREE-parsing							*/
//!\************************************************************************* */
void					cleanup_parser(t_parser *parser);
void					free_it(t_parser *parser);
void					free_arg(t_args *arg);
void					free_prev(t_parser *parser);
void					free_parser_cmd(t_parser **parser,
							t_data_cmd **cmd_data);
//!\****************************************************************/
//!											here_doc_utils_2
//!\****************************************************************/
void					open_file(char *file_name, int *fd);
void					read_lines(char *delim, int fd);
void					close_file(int fd, char *line, char *file_name);
void					h_d(char *delim, char *file_name);

//!\****************************************************************/
//!											Builtins Part
//!\****************************************************************/

void					builtins(t_args *cmd, int fd);
void					unset(t_args *cmd);
void					env(int outf);
void					ft_exit(t_args *cmd);
void					echo(t_args *input, int outf);
void					cd(t_args *cmd);
void					to_home(char *home, t_env *evr);
void					update_pwd(char *pwd, t_env *evr);
void					ft_export(t_args *cmd, int outf);
void					pwd(t_args *input, int fd);
int						builtins_check(t_args *cmd);
int						args_len(char **s);
int						foreign_letter(char *cmd);
void					get_env(char **envp);
//!\****************************************************************/
//!						parse utils
//!\****************************************************************/
int						is_redirection(t_tokens_type type);
void					in_out(int *in, int *out);
int						is_redirection_token(t_parser *parser);
int						handle_redirection(t_parser *parser, int *fd_in,
							int *fd_out, int *flag);
void					update_current_token(t_parser *parser);
//!\****************************************************************/
//!						Here doc
//!\****************************************************************/
char					*dollar(char *s, int *i);
char					*generate_filename(void);
char					*expand(char *line);
int						find(char *s, int c);
int						err_heredoc(int fd, char *file_name);
int						error_opening_file(int fd);
//!\************************************************************************* */
//!									FREE-Rein in Syntaxe				*/
//!\************************************************************************* */
void					reinitialize_parser(t_parser *parser);
int						check_ii(t_token *current, t_token *previous);
int						check_ii(t_token *current, t_token *previous);
void					free_it(t_parser *parser);
void					free_it_ii(t_parser *parser);
//!\****************************************************************/
//!												FT_List
//!\****************************************************************/

t_env					*ft_lstnew_s(char *key, char *value);
void					ft_lstadd_back_s(t_env **head, t_env *new);
t_args					*ft_lstnew_arg(void *content);
t_args					*ft_lstlast_arg(t_args *lst);
void					ft_lstadd_back_arg(t_args **lst, t_args *new);
int						ft_lstsizes(t_args *lst);
//!\****************************************************************/
//!					HERE DOC
//!\****************************************************************/
char					*generate_filename(void);
int						heredoc_file(char *delim, int *fd_in);
void					open_file(char *file_name, int *fd);
void					handle_error_and_return(char *file_name);
//!\**************************************************************** */
//!												free
//!\**************************************************************** * /

void					ft_free(t_env *evr);
void					ft_free_node(t_args *cmd);
void					ft_free_cmd_p(char **cmd);

//!\************************************************************************* */
//!											Temporary			*/
//!\************************************************************************* */

char					**ft_split_t(char const *s, char sep);
char					*epur_str(char *s);

//!\************************************************************************* */
//!										Signals 				*/
//!\************************************************************************* */

void					ctrl_d_handler(void);
void					ctrl_c_handler(int num);
void					ctrl_quit_handler(int num);
void					ctrl_handler(int num);

//!\************************************************************************* */
//!													Errors   			*/
//!\************************************************************************* */
void					print_errors(char *s);
//!\************************************************************************* */
//!										Execution				*/
//!\************************************************************************* */

void					start_execution(t_data_cmd *cmds, char **env);
void					init_execution(t_data_cmd *cmds, char **env);
void					exec_child_process(t_data_cmd *cmds, int *p1_end,
							int *p2_end, char **env);
void					dupping(t_data_cmd *cmds, int *p1_end, int *p2_end);
char					*get_path(char *cmd);
char					**to_double_pointer(t_args *cmd);
void					fds_close(t_data_cmd *cmds, int *p1_end, int *p2_end);
int						is_printable(char *s);
void					ft_err(void);		
//!\************************************************************************* */
//!										g_global Variabale			*/
//!\************************************************************************* */

t_gob					g_glob;

//!\************************************************************************* */
//!											g_global Variable.        	*/
//!\************************************************************************* */

void					rl_replace_line(const char *txt, int num);

#endif
