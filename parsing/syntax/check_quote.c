/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:22 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/04 16:12:58 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
/*
+ The function checks whether the quotes in the string are balanced or not.
*/
int	check_qutes(char *str, char q)
{
	int		i;
	int		count;
	char	type;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == q)
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
	{
		write(2, "Syntaxe Error 'Quotes'\n", 24);
		return(1);
	}
	return (0);
}
