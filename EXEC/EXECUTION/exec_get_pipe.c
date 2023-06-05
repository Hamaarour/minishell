/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 06:08:08 by zjaddad           #+#    #+#             */
/*   Updated: 2023/06/05 15:35:15 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	fds_close(t_data_cmd *cmds, int *p1_end, int *p2_end)
{
	if (cmds->fd_in != 0)
		close(cmds->fd_in);
	else if (cmds->fd_out != 1)
		close(cmds->fd_out);
	if (p2_end[0] != -42)
		close(p2_end[0]);
	if (p2_end[1] != -42)
		close(p2_end[1]);
	p2_end[0] = p1_end[0];
	p2_end[1] = p1_end[1];
	p1_end[0] = -42;
	p1_end[1] = -42;
}

void	close_files(t_data_cmd *cmds)
{
	if (cmds->fd_in)
		close(cmds->fd_in);
	if (cmds->fd_out != 1)
		close(cmds->fd_out);
}
