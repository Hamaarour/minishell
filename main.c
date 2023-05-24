/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/24 22:13:37 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "minishell.h"

void	init_glob(void)
{
	glob.ex_status = 0;
	glob.nb_cmds = 1;
}
void	welcom(void)
{
	printf("\033[0;32m╔███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░╗\n");
	printf("\033[0;32m║████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░║\n");
	printf("\033[0;32m║██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░║\n");
	printf("\033[0;32m║██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░║\n");
	printf("\033[0;32m║██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗║\n");
	printf("\033[0;32m╚╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝╝\n");
	printf("\033[0;32m\t\t\t\t\t\tHicham && Zakaria\n");
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

void	start_execution(t_data_cmd *cmds, char **env)
{
	if (builtins_check(cmds->args) != NONE_BLT && glob.nb_cmds == 1)
		builtins(cmds->args, cmds->fd_out);
	else
		init_execution(cmds, env);
}

// lets_go is the main function of the minishell
void	lets_go(t_parser *parser, char *cmd_enter, int ac, char **env)
{
	t_data_cmd	*data_cmd;

	data_cmd = NULL;
	if (ac == 1)
	{
		//welcom();
		while (1)
		{
			init_glob();
			if (read_line(&cmd_enter) == 0)
			{
				add_history(cmd_enter);
				parser = initialize_parser(cmd_enter);
				if (start_parsing(parser, &data_cmd) == 1)
					continue ;
				//system("leaks minishell");
				//print_cmd_data(&data_cmd);
				//start_execution(data_cmd, env);
				//free(cmd_enter);
				if (data_cmd)
				{
					free(data_cmd);
					data_cmd = 0;
				}
			}
			// printf("ambiguous redirect ==> %d\n", parser->lexer->ambg_redir);
			// while (parser->lexer->ambg_redir > 0)
			// {
			// 	ft_putendl_fd("Error: Ambiguous redirect", 2);
			// 	parser->lexer->ambg_redir--;
			// }
		}
		//free_parser_final(parser);
	}
	ft_putendl_fd("You cannot pass arguments to this program", 2);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	t_parser	*parser;
	char		*input;

	(void)av;
	input = NULL;
	parser = NULL;
	get_env(env);
	lets_go(parser, input, ac, env);
	printf("hello\n");
	//free_parser_final(parser);
}
