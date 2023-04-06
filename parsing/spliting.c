/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:39 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/06 02:32:45 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
spliting the string into an array of strings if there is a pipe in the string update
the pipe to -1 to be able to split the string (why -1 ? because it's not a printable
character and to separete if i find a pipe inside a double or single quotes) because
 i don't want to split the string inside the quotes .

*/
void	spliting_cmd(char *string)
{
	char	**new_s;
	int		i;

	i = 0;
	while(string[i])
	{
		if(string[i] == '\'' || string[i] == '\"')
		{
			i++;
			while(string[i] != '\'' && string[i] != '\"' && string[i])
				i++;
		}
		if(string[i] == '|')
			string[i] = -1;
		i++;
	}
	new_s = ft_split(string, -1);
	i = 0;
	while (new_s[i])
	{
		printf("%s \n", new_s[i]);
		i++;
	}

}
