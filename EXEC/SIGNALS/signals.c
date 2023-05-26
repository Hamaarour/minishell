/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 05:45:16 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/26 08:33:45 by zjaddad          ###   ########.fr       */
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
		ft_putstr_fd("Quit: 3\n", 1);
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
	rl_replace("", 0);
	ft_putstr_fd("\n→ minishell~$\n", 1);
	rl_on_new_line();
	rl_redisplay();
}
