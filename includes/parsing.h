/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:44:58 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/05 22:23:24 by hamaarou         ###   ########.fr       */
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
# include "lexer.h"

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
	int					ex_status;// an integer that represents the exit status of the last executed command.
	size_t				len_src;//len_src: an integer that represents the length of the source string
	t_env				*env;// a pointer to a t_env object that represents the environment variables.
}	t_lexer;

typedef struct s_str
{
	char		*str; //string entred by the user
	int			printed_error;// to know if i have printed an error or not
	char		**splited_str;// the string splited by pipes

}	t_str;

typedef struct s_replace_var
{
	int		i;
	int		index;
	char	*truncated_str;
	char	*new_str;
	char	*tmp;
	int		start;
	char	*last_str;

}	t_replace_var;
typedef struct s_all
{
	t_env	*env;
	int		index;
	char	**str;
}	t_all;
// typedef struct s_args
// {
// 	char	*args;
// 	t_args *next;
// }	t_args;

// typedef struct s_redirect {
// 	int type;
// 	char *file_name;
// } t_redirect;

// typedef struct Command {
// 	t_args *args;
// 	t_redirect *redrect;
// } Command;

// typedef struct s_commands
// {
// 	Command	*args;
// 	t_command *next;
// }	t_commands;

//+ Syntax
void	check_pipes(t_str *lex);
int		check_qutes(char *str, char q);
int		check_i_o_redirection(char *str);
int		check_here_doc(char *str);
int		check_append(char *str);
int		check_syntaxe(char *str);
//+ Envirment
void	get_env(t_env **env, char **envp);// get the envirment variables
//+ spliting the string
char	**spliting_cmd(t_str *str);// spliting the string by pipes
//+Expanding the envirment variables
int		check_dollar(char *str, char dollar);
int		ft_find(char *str, char c);
char	*find_var(t_env *env_p, char *var);
void	expand_var(t_str *str, t_env *env_p);
int		is_substring(char *str, char *to_find);

//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//! 							lexer functions								!//
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

t_lexer		*init_lexer(char *str);
void		advance_lexer(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer *lexer);
t_token		*get_next_token(t_lexer *lexer);
t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token);

void		error_func(int err);
char 		*get_dollar(t_lexer *lexer);
char    	*get_envairment_var(char *to_find, t_lexer *lexer);

#endif
