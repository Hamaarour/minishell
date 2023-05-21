/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:44:58 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/21 17:52:55 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "token.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 					Struct  :: the envirment variable					!//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;
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

//!+++++++++++++++++++++++++++lexer functions+++++++++++++++++++++++++++!//
t_lexer					*init_lexer(char *str);
void					advance_lexer(t_lexer *lexer);
void					lexer_skip_whitespace(t_lexer *lexer);
t_token					*get_next_token(t_lexer *lexer);
t_token	*lexer_advance_with_token(t_lexer *lexer,
									t_token *token);
t_token	*advance_to_next_tocken(t_lexer *lexer,
								t_token *token);
char					*exit_value(t_lexer *lexer);
char					*single_quote(t_lexer *lexer);

char					*envairment_var(t_lexer *lexer);
void					expand_dollar(t_lexer *lexer, char **my_str);
void	get_string_between_double_qoutes(t_lexer *lexer,
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
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 							Struct :: Parser							!//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct s_gob
{
	int					ex_status;
	int					nb_tokens;
	int					nb_cmd;
	char				**envp;
	t_env				*env_p;
}						t_gob;
typedef struct parser_struct
{
	t_lexer				*lexer;
	t_token				*current_token;
	t_token				*previous_token;
}						t_parser;

// !this struct for the args
typedef struct t_args
{
	char				*args;
	struct t_args		*next;
}						t_args;

// !this struct for the all cmd in the line

typedef struct s_data_cmd
{
	t_args				*args;
	int fd_in;  // the fd of the input 0
	int fd_out; // the fd of the output 1
	struct s_data_cmd	*next;
}						t_data_cmd;

t_parser				*initialize_parser(char *input);
void					check_max_heredoc(char *str);
void					start_parsing(t_parser *parser, t_data_cmd **cmd);
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
//!+++++++++++++++++++++++++++++++Global++++++++++++++++++++++++++++++++
t_gob					g_gob;

#endif