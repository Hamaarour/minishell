/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:55:09 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/16 06:07:28 by zjaddad          ###   ########.fr       */
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


typedef struct s_str
{
	char		*str; //string entred by the user
	int			printed_error;// to know if i have printed an error or not
	char		**splited_str;// the string splited by pipes

}	t_str;

typedef struct s_env
{
	char			*key;// the key of the envirment variable
	char			*value;// the value of the envirment variable
	//struct s_env	*prev;  // Add a pointer to the previous node
	struct s_env	*next;
}	t_env;

typedef struct  s_gob
{
	int 	ex_status;
	int 	nb_cmd;
	t_env	*env_p;
	t_env	*exprt;
	// number of command;
} t_gob;

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
	struct s_data_cmd	*next;// if there is a pipe we will have a next cmd otherwise it will be NULL if there is no pipe
}	t_data_cmd;

//////////////BUILTINS_PART/////////////////
void 	unset(t_args *cmd);
void	env(int outf);
void 	ft_exit(t_args *cmd);
void 	echo(t_args *input, int outf);
void 	cd(t_args *cmd);
void	ft_export(char **cmd, int outf);
void	pwd(t_args *input, int fd);
int		args_len(char **s);
int		foreign_letter(char *cmd);
void	ft_lstadd_back_s(t_env **head, t_env *new);
t_env	*ft_lstnew_s(char *key, char *value);
void	get_env(char **envp);
//////////////BUILTINS_PART/////////////////
//////////////FT_LST////////////////////////
t_args  *ft_lstnew_arg(void *content);
t_args  *ft_lstlast_arg(t_args *lst);
void 	ft_lstadd_back_arg(t_args **lst, t_args *new);
int 	ft_lstsizes(t_args *lst);
//////////////FT_LST////////////////////////
t_gob glob;
#endif
