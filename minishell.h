/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:55:09 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/22 20:56:24 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <errno.h>


# define STDRIN		0
# define STDROUT	1
# define STDRERR	2
# define PIPE_END	-42

# define CD			1
# define PWD		2
# define EXPORT		3
# define UNSET		4
# define ENV		5
# define EXIT		6
# define ECHO		7
# define NONE_BLT	0

//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 							Struct :: tocken 							!//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum s_tokens_type
{
	t_CHAR, // any word 0
	t_PIPE , // | 1
	t_GREAT_THAN,// > 2 
	t_LESS_THAN, // < 3
	t_HEREDOC, // << 4
	t_APPEND, // >> 5
	t_EOF, // end of file 6 
}	t_tokens_type;


typedef struct s_env
{
	char			*key;// the key of the envirment variable
	char			*value;// the value of the envirment variable
	//struct s_env	*prev;  // Add a pointer to the previous node
	struct s_env	*next;
}	t_env;


typedef struct s_tokens
{
	t_tokens_type	type;
	char			*val;
}	t_token;
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
	t_env				*env;
}						t_lexer;



typedef struct cmd {
    char* value;
    struct cmd* next;
} t_cmd;

typedef struct parser_struct
{
	t_lexer				*lexer;
	t_token				*current_token;
	t_token				*previous_token;
}						t_parser;


typedef struct  s_gob
{
	int 	ex_status;
	int 	nb_cmds;
	int		p_chld;
	t_env	*env_p;
	t_env	*exprt;
	// number of command;
} t_gob;

typedef struct s_pipes
{
	int	p1_end[2];
	int	p2_end[2];
}		t_pipes;

typedef struct s_exc
{
	t_pipes	pipe;
	int		bltns;
	int		child_pro;
	int		i;
}				t_exc;

typedef struct t_args
{
	char			*args;
	struct t_args	*next;
}	t_args;

typedef struct s_data_cmd
{
	t_args				*args;// the cmd that we will execute 
	int					fd_in;// the fd of the input 0
	int					fd_out;// the fd of the output 1
	pid_t				pid;
	struct s_data_cmd	*next;// if there is a pipe we will have a next cmd otherwise it will be NULL if there is no pipe
}	t_data_cmd;
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
t_token					*get_next_token(t_lexer *lexer);
t_token					*lexer_advance_with_token(t_lexer *lexer,
									t_token *token);
t_token					*advance_to_next_tocken(t_lexer *lexer,
								t_token *token);
char					*exit_value(t_lexer *lexer);
char					*single_quote(t_lexer *lexer);

char					*envairment_var(t_lexer *lexer);
void					expand_dollar(t_lexer *lexer, char **my_str);
void					get_string_between_double_qoutes(t_lexer *lexer,
										char **my_str);
char					*double_quote(t_lexer *lexer);
char					*hundle_quotes(t_lexer *lexer);
void					error_func(int err);
char					*get_dollar(t_lexer *lexer);
char					*get_envairment_var(char *to_find, t_lexer *lexer);
char					*get_char(t_lexer *lexer);
char					*remove_multiple_spaces(char *s);
void					get_env(char **envp);
int						check_qutes(char *str, char q);
t_token					*rederection_less(t_lexer *lexer);
t_token					*rederection_great(t_lexer *lexer);
//!+++++++++++++++++++++++++++parsing functions+++++++++++++++++++++++++++!//
t_parser				*initialize_parser(char *input);
void					check_max_heredoc(char *str);
int						start_parsing(t_parser *parser, t_data_cmd **cmd);
int						iterate_over_tokens_check_syntaxe(t_parser *parser);
int						err_msg(char *msg);
int						type_is_char(t_token *token);
int						type_is_rederec(t_token *token);
int						type_is_pipe(t_token *token);
int						type_out_in(t_token *token);
int						type_hd_apd(t_token *token);
//! +++++++++++++++++++++++++++ linked list functions ++++++++++++++++++++++++++++++++++++++++
t_data_cmd				*ft_new_cmd(t_args *arg, int fd_in, int fd_out);
void					ft_add_back_cmd(t_data_cmd **head, t_data_cmd *new);
t_args					*ft_new_arg(char *arg);
void					ft_add_back_arg(t_args **head, t_args *new);
//!+++++++++++++++++++++++++Dividing cmd+++++++++++++++++++++++++++++++++++++
t_args					*create_node(t_parser *parser, int *fd_in, int *fd_out);
void					divid_cmd(t_parser *parser, t_data_cmd **cmd_data);
//!+++++++++++++++++++++++++++++++files++++++++++++++++++++++++++++++++
void					out_file(char *file_name, t_data_cmd *tmp);
void					in_file(char *file_name, t_data_cmd *tmp);
void					append_file(char *file_name, t_data_cmd *tmp);

void					free_parser_final(t_parser *parser);

void					print_cmd_data(t_data_cmd **cmd_data);
/* ************************************************************************** */
/*		  							 Builtins Part							  */
/* ************************************************************************** */

void	builtins(t_args *cmd, int fd);
void 	unset(t_args *cmd);
void	env(int outf);
void 	ft_exit(t_args *cmd);
void 	echo(t_args *input, int outf);
void 	cd(t_args *cmd);
void	ft_export(t_args *cmd, int outf);
void	pwd(t_args *input, int fd);
int		builtins_check(t_args *cmd);
int		args_len(char **s);
int		foreign_letter(char *cmd);
void	get_env(char **envp);

/* ************************************************************************** */
/*		  							 	FT_List								  */
/* ************************************************************************** */

t_env	*ft_lstnew_s(char *key, char *value);
void	ft_lstadd_back_s(t_env **head, t_env *new);
t_args  *ft_lstnew_arg(void *content);
t_args  *ft_lstlast_arg(t_args *lst);
void 	ft_lstadd_back_arg(t_args **lst, t_args *new);
int 	ft_lstsizes(t_args *lst);

/* ************************************************************************** */
/*		  							 	free								  */
/* ************************************************************************** */

void	ft_free(t_env *evr);
void	ft_free_node(t_args *cmd);

/* ************************************************************************** */
/*		  					 		Temporary								  */
/* ************************************************************************** */

char	**ft_split_t(char const *s, char sep);
char	*epur_str(char* s);

/* ************************************************************************** */
/*		  							Signals 								  */
/* ************************************************************************** */

void	ctrl_d_handler(void);

/* ************************************************************************** */
/*		  	         	           	Errors   								  */
/* ************************************************************************** */

int	print_errors(char *s);

/* ************************************************************************** */
/*		  							Execution								  */
/* ************************************************************************** */

void	execution(t_data_cmd *cmds);

/* ************************************************************************** */
/*		  						 Global Variabale							  */
/* ************************************************************************** */

t_gob glob;

/* ************************************************************************** */
/*		  						  Global Variable  							  */
/* ************************************************************************** */
#endif