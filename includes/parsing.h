/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:44:58 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/15 00:01:06 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
# include "libft.h"
# include "token.h"

//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 				  Struct  :: the envirment variable	          		     !//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct s_env
{
	char			*key;// the key of the envirment variable
	char			*value;// the value of the envirment variable
	struct s_env	*next;
}	t_env;
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 							Struct :: lexer 							!//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct s_lexer
{
	char				*src;// a pointer to a character array that represents the source string to be tokenized.
	char				c; // a character that represents the current character being processed in the source string.
	unsigned int		i; //an integer that represents the index of the current haracter in the source string
	size_t				len_src;//len_src: an integer that represents the length of the source string
	t_env				*env;// a pointer to a t_env object that represents the environment variables.
}	t_lexer;

//!+++++++++++++++++++++++++++lexer functions+++++++++++++++++++++++++++!//
t_lexer		*init_lexer(char *str);
void		advance_lexer(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer *lexer);
t_token		*get_next_token(t_lexer *lexer);
t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token);
char		*exit_value(t_lexer *lexer);
char		*single_quote(t_lexer *lexer);
char		*envairment_var(t_lexer *lexer);
void		expand_dollar(t_lexer *lexer, char **my_str);
void		get_string_between_double_qoutes(t_lexer *lexer, char **my_str);
char		*double_quote(t_lexer *lexer);
char		*hundle_quotes(t_lexer *lexer);
void		error_func(int err);
char 		*get_dollar(t_lexer *lexer);
char    	*get_envairment_var(char *to_find, t_lexer *lexer);
char		*get_char(t_lexer *lexer);
char		*remove_multiple_spaces(char* s);
void		get_env(char **envp);// get the envirment variables
int			check_qutes(char *str, char q);// check if the qutes are balanced


//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 							Struct :: Parser							!//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct  s_gob
{
	int 	ex_status;
	int 	nb_tokens;// number of pipe;
	int 	nb_cmd;// number of command == nmbr of pipes;
	char 	**envp;
	t_env	*env_p;
} t_gob;
typedef struct parser_struct
{
	t_lexer		*lexer;
	t_token		*current_token;
	t_token		*previous_token;
}	t_parser;

// !this struct for the args
typedef struct t_args
{
	char			*args;
	struct t_args	*next;
}	t_args;

// !this struct for the all cmd in the line
typedef struct s_data_cmd
{
	t_args				*args;// the cmd that we will execute 
	int					fd_in;// the fd of the input 0
	int					fd_out;// the fd of the output 1
	struct s_data_cmd	*next;// if there is a pipe we will have a next cmd otherwise it will be NULL if there is no pipe
}	t_data_cmd;


t_parser	*initialize_parser(char *input);// init_parser will create a parser object and return it 
void		check_max_heredoc(char *str);// check_max_heredoc will check if the heredoc "<<" is not more than 16
void    	start_parsing(t_parser *parser, char *input, t_data_cmd **cmd);// start_parsing will start parsing the input and return the head of the linked list
int			iterate_over_tokens_check_syntaxe(t_parser *parser, char *cmd);
void		parser_free(t_parser *parser);
int			err_msg(char *msg);
void		free_tocken(t_token *token);
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
t_data_cmd	*ft_new_cmd(t_args *args);//creat new node of t_data_cmd type and return it
void		ft_add_back_cmd(t_data_cmd **head, t_data_cmd *new);// add back the new node to the linked list
t_args		*ft_new_arg(char *arg);//creat new node of t_args type and return it
void		ft_add_back_arg(t_args **head, t_args *new);// add back the new node to the linked list



//!+++++++++++++++++++++++++++++++Global++++++++++++++++++++++++++++++++
t_gob 		g_gob;



#endif