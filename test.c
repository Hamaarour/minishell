#include "builtins.h"
#include "../libft/libft.h"
#include "minishell.h"

void	check_builtin(char **cmd, int fd, t_env	*envr)
{
	if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd, fd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		pwd(cmd, fd);
	else if (!ft_strcmp(cmd[0], "unset"))
		unset(cmd, envr);
	else if (!ft_strcmp(cmd[0], "env"))
		env(envr, fd);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd, envr);
	else
		printf("NO BUILTINS\n");
	// else if (!ft_strcmp(cmd[i], "export"))
	// 	export();
	// else
	// 	execute();
}

int main(int ac, char **av, char **env) {
	t_env	*envr;
    int i = 0;
	int	fd = 1;
	char *input;
	char *ss;
	char	**cmd_prt;

	get_env(&envr, env);
	while (1)
	{
		input = readline("\033[0;32mExecution =>> ");
		add_history (input);
		if (!input || input[0] == '\0')
			continue ;
		ss = epur_str(input);
		cmd_prt =  ft_split(ss, ' ');
		check_builtin(cmd_prt, fd, envr);
		while(cmd_prt[i])
			free(cmd_prt[i++]);
		free(cmd_prt);
		free(input);
		free(ss);
		i = 0;
	}
    return 0;
}
