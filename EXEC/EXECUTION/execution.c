/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:23:00 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/22 02:09:19 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	pipe_creation(t_pipes *pipes)
{
	if (pipe(pipes->p1_end) == -1)
		exit(print_errors("Pipe Error"));
	if (pipe(pipes->p2_end) == -1)
		exit(print_errors("Pipe Error"));
}

void	execution(t_data_cmd *cmds)
{
	t_exc	exc;

	pipes_creation(&exc.pipe);
	exc.i = -1;
	while (++exc.i < glob.nb_cmdss)
	{
		get_pip_fd(&exc.pipe, cmds[exc.i]);
		exc.bltns = builtins_check(cmds[exc.i].args);
		if (exc.bltns != NONE_BLT && glob.nb_cmdss == 1)
			builtins(cmds[exc.i].args, cmds[exc.i].fd_out);
		else
		{
			glob.p_chld = 1;
			cmds[exc.i].pid = fork();
			if (cmds[exc.i].pid == -1)
				exit(print_error("Pipe Error"));
			else if (cmds[exc.i].pid == 0)
				execute_cmd(cmds[exc.i], &exc.pipe, exc.bltns);
		}
	}
	close_file_desc(cmds, &exc.pipe);
	if (glob.p_chld)
		wait_childs(cmds);
	free_data_cmds(cmds);
}