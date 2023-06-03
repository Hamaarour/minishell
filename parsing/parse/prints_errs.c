/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_errs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:43:35 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/03 16:59:33 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	ft_err(void)
{
	while (g_glob.ambg_redir > 0)
	{
		g_glob.ex_status = 1;
		ft_putendl_fd("Error: Ambiguous redirect", 2);
		g_glob.ambg_redir--;
	}
	while (g_glob.nb_err > 0)
	{
		g_glob.ex_status = 1;
		ft_putendl_fd("bash: No such file or directory", 2);
		g_glob.nb_err--;
	}
}
