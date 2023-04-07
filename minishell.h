#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include "Utils/lib_utils/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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
typedef struct s_all
{
	t_env	*env;
	int		index;
	char	**str;
}	t_all;


//+ Syntax
void	check_pipes(t_str *lex);
void	check_qutes(char *str);
int		check_i_o_redirection(char *str);
int		check_here_doc(char *str);
int		check_append(char *str);
int		check_syntaxe(char *str);
//+ Envirment
void		get_env(t_env **env, char **envp);// get the envirment variables
//+ spliting the string
char		**spliting_cmd(t_str *str);// spliting the string by pipes
//+Expanding the envirment variables

#endif
