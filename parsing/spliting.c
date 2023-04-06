/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:39 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/05 16:51:47 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	spliting_cmd(t_str *string)
{
	char	**new_s;
	int		i;
	while(string->str[i])
	{
		if(string->str[i] == '\'' || string->str[i] == '\"')
		{
			i++;
			while(string->str[i] != '\'' || string->str[i] != '\"')
				i++;
		}
		if(string->str[i] == '|')
		{
			string->str[i] = -1;
		}

	}

}
