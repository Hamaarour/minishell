/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:22 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/23 12:54:21 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/*
+ The function checks whether the quotes in the string are balanced or not.
*/
int	check_qutes(t_lexer *lexer, char q)
{
	int	begin;

	// int		i;
	// int		count;
	// char	type;
	// i = 0;
	// count = 0;
	// while (str[i] != '\0')
	// {
	// 	if (str[i] == q)
	// 	{
	// 		type = str[i++];
	// 		count++;
	// 		while (str[i] != '\0' && str[i] != type)
	// 			i++;
	// 		if (str[i] == type)
	// 		{
	// 			count++;
	// 			i++;
	// 		}
	// 	}
	// 	else
	// 		i++;
	// }
	// if (count % 2 != 0)
	// 	return (1);
	// return (0);
	begin = lexer->i;
	while (lexer->src[begin] != '\0')
	{
		if (lexer->src[begin] == q)
			return (1);
		begin++;
	}
	return (0);
}
