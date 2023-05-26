/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:25:00 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/26 00:20:10 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

int	check_newline(char *s)
{
	int	i;

	i = 2;
	if (s[0] != '-' || (s[0] == '-' && s[1] != 'n'))
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] && s[i] != 'n')
		return (0);
	return (1);
}

void echo(t_args *input, int outf)
{
    int 	i;
    int 	flag;
	t_args	*tmp;

    //glob.ex_status = 0;
    flag = 1;
    i = 1;
	tmp = input;
	tmp = tmp->next;
    while (tmp && check_newline(tmp->args))
    {
        flag = 0;
        while (tmp && check_newline(tmp->args))
            tmp = tmp->next;
    }
    while (tmp)
    {
        ft_putstr_fd(tmp->args, outf);
        tmp = tmp->next;
        if (tmp)
            ft_putstr_fd(" ", outf);
    }
    if (flag)
        ft_putstr_fd("\n", outf);
}
