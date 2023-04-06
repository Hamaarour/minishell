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
	char	*str;
	int		printed_error;
}	t_str;
typedef struct s_env
{
	char			*key;
	char			*value;
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

void	get_env(t_env **env, char **envp);
void	spliting_cmd(char *string);
#endif
