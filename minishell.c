/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/19 15:21:40 by hamaarou         ###   ########.fr       */
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

// lets_go is the main function of the minishell
void	lets_go(t_parser *parser, char *cmd_enter, int ac)
{

	(void)parser;

	t_data_cmd	*data_cmd;

	data_cmd = NULL;
	if (ac == 1)
	{
		while(1)
		{
			init_g_gob();
			if (read_line(&cmd_enter) == 0)
			{
				add_history(cmd_enter);
				parser = initialize_parser(cmd_enter);
				start_parsing(parser, cmd_enter, &data_cmd);
				//print_cmd_data(&data_cmd);
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
	t_parser 	*parser;
	char		*input;
	
	input = NULL;
	parser = NULL;
	get_env(env);
	lets_go(parser, input, ac);
}