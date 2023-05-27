/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:15 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/27 20:45:58 by hamaarou         ###   ########.fr       */
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
		ft_putendl_fd("bash: maximum here-document count exceeded: 16", 2);
		glob.ex_status = 2;
		return (1);
	}
	return (0);
}