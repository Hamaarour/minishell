/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:22 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/09 18:38:10 by hamaarou         ###   ########.fr       */
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
		ft_putendl_fd("Syntaxe Error 'Quotes'", 2);
		g_gob.ex_status = 258;
		return(1);
	}
	return (0);
}
