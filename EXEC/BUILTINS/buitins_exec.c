/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:20:06 by zjaddad           #+#    #+#             */
/*   Updated: 2023/06/05 15:04:14 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

int	builtins_check(t_args *cmd)
{
	if (!ft_strcmp(cmd->args, "echo"))
		return (ECHO);
	else if (!ft_strcmp(cmd->args, "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd->args, "cd"))
		return (CD);
	else if (!ft_strcmp(cmd->args, "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd->args, "env"))
		return (ENV);
	else if (!ft_strcmp(cmd->args, "exit"))
		return (EXIT);
	else if (!ft_strcmp(cmd->args, "export"))
		return (EXPORT);
	return (NONE_BLT);
}

void	builtins(t_args *cmd, int fd)
{
	if (!ft_strcmp(cmd->args, "echo"))
		echo(cmd, fd);
	else if (!ft_strcmp(cmd->args, "pwd"))
		pwd(cmd, fd);
	else if (!ft_strcmp(cmd->args, "cd"))
		cd(cmd);
	else if (!ft_strcmp(cmd->args, "unset"))
		unset(cmd);
	else if (!ft_strcmp(cmd->args, "env"))
		env(fd);
	else if (!ft_strcmp(cmd->args, "exit"))
		ft_exit(cmd);
	else if (!ft_strcmp(cmd->args, "export"))
		ft_export(cmd, fd);
	return ;
}
