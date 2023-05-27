/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/27 10:45:47 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "minishell.h"

void	init_glob(void)
{
	glob.ex_status = 0;
	glob.p_chld = 0;
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
	*line = readline("→ minishell~$ ");
	if (*line == NULL)
		ctrl_d_handler();
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

void	free_to(t_token *tocken)
{
	if (tocken != NULL)
	{
		if (tocken->type != t_CHAR)
		{
			if (tocken->val)
				free(tocken->val);
		}
		if (tocken)
			free(tocken);
	}
}
void	free_p(t_parser *parser)
{
	if (parser != NULL)
	{
		if (parser->lexer != NULL)
		{
			free(parser->lexer->src);
			free(parser->lexer);
		}
		if (parser->previous_token)
			free_to(parser->previous_token);
		if (parser->current_token)
			free_to(parser->current_token);
	}
}
// lets_go is the main function of the minishell
void	lets_go(t_parser *parser, char *cmd_enter, int ac, char **env)
{
	t_data_cmd	*data_cmd;

	data_cmd = NULL;
	if (ac == 1)
	{
		// welcom();
		init_glob();
		while (1)
		{
			signal(SIGINT, ctrl_c_handler);
			signal(SIGQUIT, SIG_IGN);
			if (read_line(&cmd_enter) == 0)
			{
				add_history(cmd_enter);
				parser = initialize_parser(cmd_enter);
				if (parser == NULL || start_parsing(parser, &data_cmd) == 1)
				{
					continue ;
				}
				start_execution(data_cmd, env);
				free(cmd_enter);
				if (data_cmd)
				{
					free(data_cmd);
					data_cmd = 0;
				}
			}
		}
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
}
