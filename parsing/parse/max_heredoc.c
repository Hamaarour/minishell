/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:15 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/06 17:46:15 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

int	max_heredoc(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			count++;
		i++;
	}
	if (count > 16)
	{
		ft_putendl_fd("\033[1;31mbash: maximum here-document count exceeded: 16\033[1;0m", 2);
		g_glob.ex_status = 2;
		return (1);
	}
	return (0);
}
