/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 05:45:16 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/31 16:43:04 by hamaarou         ###   ########.fr       */
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
	g_glob.ex_status = 131;
	ft_putstr_fd("Quit: 3\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_c_handler(int num)
{
	(void)num;
	g_glob.ex_status = 1;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_handler(int num)
{
	(void)num;
	ft_putstr_fd("\n", 1);
	exit(1);
}
