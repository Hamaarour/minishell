/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:59:40 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/11 02:42:39 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "../libft/libft.h"

void	print_error(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		printf("Options are forbidden!\n");
}

void	pwd(char **input, int fd)
{
	glob.ex_status = 0;
	if (input[0] && input[1])
		if (input[1][0] == '-' && input[1][1])
			return (print_error(input[0]));
	ft_putstr_fd(getcwd(NULL, 0), fd);
	ft_putstr_fd("\n", fd);
}