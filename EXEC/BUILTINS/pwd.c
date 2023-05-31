/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:59:40 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/31 16:43:04 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	print_error(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		printf("Options are forbidden!\n");
}

void	pwd(t_args *input, int fd)
{
	char	*str;

	g_glob.ex_status = 0;
	if (input && input->next != NULL)
		if (input->next->args[0] == '-' && input->next->args[1])
			return (print_error(input->args));
	str = getcwd(NULL, 0);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	free(str);
}
