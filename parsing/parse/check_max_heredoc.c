/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_max_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:15 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/09 12:33:32 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	check_max_heredoc(char *str)
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
		ft_putendl_fd("bash: maximum here-document count exceeded: 16", 2);
		g_gob.ex_status = 2;
		exit(EXIT_FAILURE);
	}
}