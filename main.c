/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/26 23:30:00 by hamaarou         ###   ########.fr       */
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
	// if (*line == NULL)
	// 	ctrl_d_handler();
	if (*line == NULL)
	{
		free(*line);
		exit(0);
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
	//printf("in = %d.  out = %d\n", cmds->fd_in, cmds->fd_out);
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
		//welcom();
		init_glob();
		while (1)
		{
			//signal(SIGINT, ctrl_c_handler);
			//signal(SIGQUIT, SIG_IGN);
			if (read_line(&cmd_enter) == 0)
			{
				add_history(cmd_enter);
				parser = initialize_parser(cmd_enter);
				if (parser == NULL || start_parsing(parser, &data_cmd) == 1)
					continue ;
				// printf("lexer = 			%p\n", parser->lexer);
				// printf("current_token_val = %p\n",
				// 		parser->current_token->val);
				// printf("current_token = 	%p\n", parser->current_token);
				// printf("parser = 			%p\n", parser);
				// // if (parser != NULL)
				// {
				//system("leaks minishell");
				//print_cmd_data(&data_cmd);
				//start_execution(data_cmd, env);
				free(cmd_enter);
				// if (data_cmd)
				// {
				// 	free(data_cmd);
				// 	data_cmd = 0;
				// }
			}
		}
		if (parser->lexer != NULL)
			free(parser->lexer);
		if (parser->current_token != NULL)
		{
			if (parser->current_token->val != NULL)
				free(parser->current_token->val);
			free(parser->current_token);
		}
		free(parser);
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
	//free_parser_final(parser);
}
