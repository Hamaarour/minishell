/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/04 20:09:49 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "minishell.h"

void	init_g_glob(void)
{
	g_glob.ex_status = 0;
	g_glob.p_chld = 0;
	g_glob.nb_cmds = 1;
	g_glob.fd_here_doc = 0;
	g_glob.to_expand = 0;
	g_glob.nb_err = 0;
	g_glob.ambg_redir = 0;
}

int	read_line(char **line)
{
	char	*trimmed_line;
	char	*end;
	char	*start;

	*line = readline("→ minishell~$ ");
	if (*line == NULL)
		ctrl_d_handler();
	trimmed_line = ft_strdup(*line);
	end = trimmed_line + ft_strlen(trimmed_line) - 1;
	while (end > trimmed_line && ft_isspace(*end))
		end--;
	*(end + 1) = '\0';
	start = trimmed_line;
	while (*start && ft_isspace(*start))
		start++;
	if (*start == '\0')
	{
		free(*line);
		free(trimmed_line);
		return (1);
	}
	free(*line);
	*line = trimmed_line;
	return (0);
}

void	start_execution(t_data_cmd *cmds, char **env)
{
	if (builtins_check(cmds->args) != NONE_BLT && g_glob.nb_cmds == 1)
		builtins(cmds->args, cmds->fd_out);
	else
		init_execution(cmds, env);
}

void	lets_go(t_parser *parser, char *cmd, char **env, t_data_cmd *data)
{
	while (1)
	{
		g_glob.to_expand = 0;
		g_glob.nb_err = 0;
		g_glob.ambg_redir = 0;
		signal(SIGINT, ctrl_c_handler);
		signal(SIGQUIT, SIG_IGN);
		if (read_line(&cmd) == 0)
		{
			add_history(cmd);
			if (max_heredoc(cmd) == 0)
			{
				parser = initialize_parser(cmd);
				if (parser == NULL || start_parsing(parser, &data) == 1)
					continue ;
				ft_err();
				if (data != NULL)
					start_execution(data, env);
				free_parser_cmd(&parser, &data);
			}
			free(cmd);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_parser	*parser;
	char		*input;
	t_data_cmd	*data_cmd;

	(void)av;
	input = NULL;
	parser = NULL;
	data_cmd = NULL;
	if (ac != 1)
		exit(EXIT_FAILURE);
	init_g_glob();
	get_env(env);
	lets_go(parser, input, env, data_cmd);
}
