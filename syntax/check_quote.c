/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:22 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/01 00:29:24 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
+ The function checks whether the quotes in the string are balanced or not.
*/
void	check_qutes(char *str)
{
	int		i;
	int		count;
	char	type;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			type = str[i++];
			count++;
			while (str[i] != '\0' && str[i] != type)
				i++;
			if (str[i] == type)
			{
				count++;
				i++;
			}
		}
		else
			i++;
	}
	if (count % 2 != 0)
		printf("Error: Syntax error\n");
}
