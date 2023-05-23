/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:23:00 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/23 04:39:21 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

// void	pipe_creation(t_pipes *pipes)
// {
// 	if (pipe(pipes->p1_end) == -1)
// 		exit(print_errors("Pipe Error"));
// 	if (pipe(pipes->p2_end) == -1)
// 		exit(print_errors("Pipe Error"));
// }

// void	execution(t_data_cmd *cmds)
// {

// 	t_exc	exc;
// 	pipes_creation(&exc.pipe);
// 	exc.i = -1;
// 	while (++exc.i < glob.nb_cmdss)
// 	{
// 		get_pip_fd(&exc.pipe, cmds[exc.i]);
// 		exc.bltns = builtins_check(cmds[exc.i].args);
// 		if (exc.bltns != NONE_BLT && glob.nb_cmdss == 1)
// 			builtins(cmds[exc.i].args, cmds[exc.i].fd_out);
// 		else
// 		{
// 			glob.p_chld = 1;
// 			cmds[exc.i].pid = fork();
// 			if (cmds[exc.i].pid == -1)
// 				exit(print_error("Pipe Error"));
// 			else if (cmds[exc.i].pid == 0)
// 				execute_cmd(cmds[exc.i], &exc.pipe, exc.bltns);
// 		}
// 	}
// 	close_file_desc(cmds, &exc.pipe);
// 	if (glob.p_chld)
// 		wait_childs(cmds);
// 	free_data_cmds(cmds);
// }

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

void	exec_child_process(t_data_cmd *cmds, int *p1_end, int *p2_end)
{
	dupping(cmds, p1_end, p2_end);
	if (builtins_check(cmds->args))
	{
		builtins(cmds->args, cmds->fd_out);
		exit(0);
	}
	
}

void	execution(t_data_cmd *cmds, int *p1_end, int *p2_end)
{
	while (cmds)
	{
		if (cmds->next)
		{
			if (pipe(p1_end) == -1)
				return ;
		}
		cmds->pid = fork();
		if (cmds->pid == 0)
			exec_child_process(cmds, p1_end, p2_end);
		cmds = cmds->next;
	}
}

void	init_execution(t_data_cmd *cmds)
{
	int	p1_end[2];
	int	p2_end[2];

	p1_end[0] = -42;
	p1_end[1] = -42;
	p2_end[0] = -42;
	p2_end[1] = -42;
	execution(cmds, p1_end, p2_end);
}
