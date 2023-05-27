/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:23:00 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/27 10:47:51 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	redirections(int infile, int outfile)
{
	if (infile)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != 1)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}

void	dupping(t_data_cmd *cmds, int *p1_end, int *p2_end)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmds->next)
	{
		close(p1_end[0]);
		dup2(p1_end[1], 1);
		close(p1_end[1]);
	}
	if (p2_end[0] != -42)
	{
		close(p2_end[1]);
		dup2(p2_end[0], 0);
		close(p2_end[1]);
	}
	redirections(cmds->fd_in, cmds->fd_out);
}

void	exec_child_process(t_data_cmd *cmds, int *p1_end, int *p2_end,
		char **env)
{
	char	**cmd_arg;

	signal(SIGQUIT, ctrl_quit_handler);
	dupping(cmds, p1_end, p2_end);
	if (builtins_check(cmds->args))
	{
		builtins(cmds->args, cmds->fd_out);
		exit(0);
	}
	cmd_arg = to_double_pointer(cmds->args);
	cmd_arg[0] = get_path(cmd_arg[0]);
	if (is_printable(cmd_arg[0]))
	{
		if (execve(cmd_arg[0], cmd_arg, env) == -1)
		{
			write(2, "minishell$: command not found\n", 30);
			glob.ex_status = 127;
			exit(glob.ex_status);
		}
	}
	else
		exit(1);
	ft_free_cmd_p(cmd_arg);
}

void	execution(t_data_cmd *cmds, int *p1_end, int *p2_end, char **env)
{
	t_data_cmd	*tmp;

	tmp = cmds;
	while (cmds)
	{
		if (cmds->next)
			if (pipe(p1_end) == -1)
				return ;
		signal(SIGINT, SIG_IGN);
		cmds->pid = fork();
		if (cmds->pid == 0)
		{
			exec_child_process(cmds, p1_end, p2_end, env);
		}
		fds_close(cmds, p1_end, p2_end);
		cmds = cmds->next;
	}
	while (tmp)
	{
		waitpid(tmp->pid, &glob.ex_status, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(glob.ex_status))
		glob.ex_status = WEXITSTATUS(glob.ex_status);
	else
		glob.ex_status += 128;
}

void	init_execution(t_data_cmd *cmds, char **env)
{
	int p1_end[2];
	int p2_end[2];

	p1_end[0] = -42;
	p1_end[1] = -42;
	p2_end[0] = -42;
	p2_end[1] = -42;
	execution(cmds, p1_end, p2_end, env);
}