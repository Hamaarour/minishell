/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:13:02 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/24 01:13:32 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution_child(t_list *cmds, t_parser *tmp, int *pipe1, int *buffer)
{
	dup_std_io(cmds, tmp, pipe1, buffer);
	if (check_builtin(cmds))
	{
		builtins(cmds);
		exit (0);
	}
	tmp->cmd[0] = add_path(tmp->cmd[0]);
	if (check_cmd(tmp->cmd[0]))
	{
		if (execve(tmp->cmd[0], tmp->cmd, tmp->env) == -1)
		{
			write(2, "minishell : command not found\n", 30);
			g_data.exit_status = 127;
			exit(g_data.exit_status);
		}
	}
	else
		exit(1);
}

void	closing_fds(t_parser *tmp, int *pipe1, int *buffer)
{
	unlink("/tmp/minishell");
	if (tmp->in_file != 0)
		close(tmp->in_file);
	else if (tmp->out_file != 1)
		close(tmp->out_file);
	if (buffer[0] != -1)
		close(buffer[0]);
	if (buffer[1] != -1)
		close(buffer[1]);
	buffer[0] = pipe1[0];
	buffer[1] = pipe1[1];
	pipe1[0] = -1;
	pipe1[1] = -1;
}

void	execution_loop(t_list *cmds, t_parser *tmp, int *pipe1, int *buffer)
{
	int	pid;

	while (cmds)
	{
		tmp = (t_parser *)cmds->content;
		if (cmds->next)
		{
			if ((pipe(pipe1) == -1))
				return ;
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			execution_child(cmds, tmp, pipe1, buffer);
		closing_fds(tmp, pipe1, buffer);
		cmds = cmds->next;
	}
	while (waitpid(pid, &g_data.exit_status, 0) != -1)
		;
	if (WIFEXITED(g_data.exit_status))
		g_data.exit_status = WEXITSTATUS(g_data.exit_status);
	else
		g_data.exit_status = 128 + WTERMSIG(g_data.exit_status);
}

void	execute(t_list *cmds)
{
	int			pipe1[2];
	int			buffer[2];
	t_parser	*tmp;

	pipe1[0] = -1;
	pipe1[1] = -1;
	buffer[0] = -1;
	buffer[1] = -1;
	tmp = (t_parser *) s_malloc(sizeof(t_parser));
	execution_loop(cmds, tmp, pipe1, buffer);
}

void	start(t_list *list)
{
	t_parser	*cmd;

	cmd = (t_parser *) s_malloc(sizeof(t_parser));
	cmd = (t_parser *)list->content;
	if (ft_lstsize(list) == 1 && check_builtin(list))
		builtins(list);
	else
	{
		cmd->env = env_to_tab(g_data.env);
		execute(list);
	}
}