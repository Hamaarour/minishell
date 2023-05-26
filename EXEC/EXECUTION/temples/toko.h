/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toko.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:12 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/26 18:40:00 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H
# include <signal.h>
#include "../lib_ft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/stat.h>

typedef struct s_lexer
{
	char	*src;
	int	index;
	char	c;
}	t_lexer;

typedef struct s_global_data{
	int		exit_status;
	void	*to_free[1000000];
	int		index;
	t_list	*env;
}	t_global_data;

t_global_data	g_data;

typedef struct s_parser
{
	char	**cmd;
	int		in_file;
	int		out_file;
	char	**env;
}	t_parser;

typedef struct s_token
{
	char	*value;
	enum
	{
		TOKEN_STRING,
		TOKEN_REDIRECT,
		TOKEN_LREDIRECT,
		TOKEN_APPEND,
		TOKEN_HEREDOC,
		TOKEN_PIPE,
		TOKEN_EOF,
	}type;
}	t_token;

typedef struct s_env
{
	char	*key;
	char	separateur;
	char	*value;
}	t_env;

          //lexer//
void	init_lexer(t_lexer *lexer ,char *src);
void	lexer_next(t_lexer * lexer);
void	skip_spaces(t_lexer *lexer);
char	*append_to_str(char *str , char c);
t_list	*lexer(char *src);

          //tokenizer//
t_token	*init_token(char *value, int type);
t_token	*_switch(t_lexer *lexer);
t_token	*get_token(t_lexer *lexer);
void	debug_print_token(t_token *token);
int		istoken(char c);
        
          //parser//
t_list	*fill_command(t_list *tokens);
int		check_syntax(t_list *tokens);
void	init_parser(t_parser *cmd);
t_parser	*init_content(t_parser *content);
int		quotes_checker(char *str);
char	*remove_quotes(char *str , int *heredoc_flag, int prev_type);
t_list	*parsing_quotes(t_list *tokens, int *flag);
int	lredirection_handler(t_list *tokens, t_parser *tmp);
int	heredoc_and_append_handler(t_list **tokens, t_parser **tmp, int flag);
void	add_cmd_to_list(t_token *curr, t_list **cmd_list, t_parser **tmp);
t_token	*go_next(t_list **tokens);


        //parser_utils.c//
void	deallocate(t_list *list);
void	ft_free(char	**t);
char	**realloc_cmd(char **cmd, char *str);
void	debug_print_token(t_token *token);
void	print_tokens(t_list *list);
void	print_cmd(t_list *list);
char	*expand(char *result, char *var_name);
char	*get_var_name(char *str);
char	*expanding(char *str);

       //execution_utils.c//
t_list	*get_env(char **env);
size_t	get_env_size(char **env);
char	*add_path(char *cmd);
char	**env_to_tab(t_list *list);
void	*s_malloc(int size);
int		check_cmd(char *str);
void	dup_std_io(t_list *cmds, t_parser *tmp, int *pipe1, int *buffer);

      //builtins//
void	builtins(t_list *list);
void	ft_unset(char **var);
void	ft_env(int fd);
void	ft_export(char **var, int fd);
void	ft_pwd(int fd);
void	ft_echo(char **s, int fd);
void	ft_exit(char **s);
void	ft_cd(char **s);
int		size_par(char **s);
char	*get_new_env(char *s);
int		check_builtin(t_list *list);

      //execut//
void		start(t_list *list);
void	execute(t_list *cmds);

      // signlas // 
void	handler(int sig);
void	rl_replace_line(char *, int);

      //heredoc//
int	heredoc(char *value, int flag);

#endif
