/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:39 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/07 02:16:12 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
spliting the string into an array of strings if there is a pipe in the string update
the pipe to -1 to be able to split the string (why -1 ? because it's not a printable
character and to separete if i find a pipe inside a double or single quotes) because
 i don't want to split the string inside the quotes .

*/
char	**spliting_cmd(t_str *str)
{
	int		i;

	i = 0;
	while(str->str[i])
	{
		if(str->str[i] == '\'' || str->str[i] == '\"')
		{
			i++;
			while(str->str[i] != '\'' && str->str[i] != '\"' && str->str[i])
				i++;
		}
		if(str->str[i] == '|')
			str->str[i] = -1;
		i++;
	}
	str->splited_str = ft_split(str->str, -1);
	return (str->splited_str);
}
