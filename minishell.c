/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/13 21:53:06 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

void	init_g_gob(void)
{
	g_gob.ex_status = 0;
	g_gob.nb_cmd = 0;
}

int	read_line(char **line)
{
	*line = readline("minishell~$ ");
	if (*line == NULL)
	{
		free(*line);
		exit(EXIT_SUCCESS);
	}
	if (line[0][0] == '\0')
	{
		free(*line);
		return (1);
	}
	return (0);
}

void	lets_go(t_parser *parser, t_cmd *args,char *cmd_enter, int ac)
{
	if (ac == 1)
	{
		while(1)
		{
			g_gob.nb_cmd = 0;
			if (read_line(&cmd_enter) == 0)
			{
				add_history(cmd_enter);
				parser = initialize_parser(cmd_enter);
				args = start_parsing(parser, cmd_enter);
				printf("nb_cmd = %d\n", g_gob.nb_cmd);
				printf("ex_status = %d\n", g_gob.ex_status);
				free(cmd_enter);
			}
		}
	}
	ft_putendl_fd("You cannot pass arguments to this program", 2);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	t_env	*env_p;
	t_parser *parser;
	t_cmd	*cmd;
	char	*input;
	
	g_gob.ex_status = 0;
	g_gob.nb_cmd = 0;
	
	input = NULL;
	parser = NULL;
	cmd = NULL;
	get_env(&env_p, env);
	lets_go(parser, cmd, input, ac);
}


// ? test token 
	// t_lexer *lexer;
	// t_token *token;
 	// 	lexer = init_lexer("ls -l |   \"$USER\" >>");
	// lexer->env = env_p;
    // token = get_next_token(lexer);
	
    // while (token->type != t_EOF)
    // {
    //     printf("Token ( %d , %s)\n", token->type, token->val);
	// 	free(token->val);
	// 	free(token);
    //     token = get_next_token(lexer);
    // }
	//system("leaks minishell");