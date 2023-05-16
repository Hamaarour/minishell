/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/16 14:42:43 by hamaarou         ###   ########.fr       */
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
void print_args(t_data_cmd *data_cmd) {
    while (data_cmd != NULL) {
        while (data_cmd->args != NULL) {
            printf("--%s--", data_cmd->args->args);
            data_cmd->args = data_cmd->args->next;
        }
        printf("****************************\n");
        data_cmd = data_cmd->next;
    }
}
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
				print_args(data_cmd);
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