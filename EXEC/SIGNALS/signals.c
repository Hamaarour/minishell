/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 05:45:16 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/26 11:05:51 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	ctrl_d_handler(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	ctrl_quit_handler(int num)
{
	(void)num;
	if (glob.p_chld)
	{
		glob.ex_status = 131;
		ft_putstr_fd("Quit: 3\n", 1);
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_c_handler(int num)
{
	(void)num;
	glob.ex_status = 1;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
