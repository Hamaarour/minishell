/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:16:33 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/17 18:45:52 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft/libft.h"
#include "builtins.h"
#include "minishell.h"

void	env(int outf)
{
	t_env *tmp;

	tmp = glob.env_p;
	glob.ex_status = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, outf);
			ft_putstr_fd("=", outf);
			ft_putstr_fd(tmp->value, outf);
			ft_putstr_fd("\n", outf);
		}
		tmp = tmp->next;
	}
}
