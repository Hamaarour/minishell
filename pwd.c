/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:59:40 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/17 00:13:33 by zjaddad          ###   ########.fr       */
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

void pwd(t_args *input, int fd)
{
    glob.ex_status = 0;
    if (input && input->next != NULL)
        if (input->next->args[0] == '-' && input->next->args[1])
            return (print_error(input->args));
    char * str = getcwd(NULL, 0);
	ft_putstr_fd(str, fd);
    ft_putstr_fd("\n", fd);
	free(str);
}