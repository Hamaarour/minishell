/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:35:15 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/05 00:56:32 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	err_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	g_glob.ex_status = 258;
	g_glob.nb_cmds = 0;
}

void	ft_put(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
}

int	err_msg_ii(char *msg)
{
	ft_put(msg, 2);
	g_glob.ex_status = 258;
	g_glob.nb_cmds = 0;
	return (258);
}

int	error_opening_file(int fd)
{
	if (fd == -1)
	{
		g_glob.nb_err++;
		g_glob.ex_status = 1;
		return (1);
	}
	return (0);
}

int	err_heredoc(int fd, char *file_name)
{
	if (fd == -1)
	{
		g_glob.nb_err++;
		g_glob.ex_status = 1;
		free(file_name);
		return (1);
	}
	return (0);
}
