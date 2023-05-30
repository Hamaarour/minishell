/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:35:15 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/29 11:16:30 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

int	err_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	glob.ex_status = 258;
	glob.nb_cmds = 0;
	return (258);
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

int	err_msg_II(char *msg)
{
	ft_put(msg, 2);
	glob.ex_status = 258;
	glob.nb_cmds = 0;
	return (258);
}

void	error_opening_file(int fd)
{
	if (fd == -1)
	{
		ft_putendl_fd("Bash Error: No such file or directory", 2);
		glob.ex_status = 1;
	}
}