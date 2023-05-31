/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:22 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/31 16:25:21 by hamaarou         ###   ########.fr       */
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

	begin = lexer->i;
	while (lexer->src[begin] != '\0')
	{
		if (lexer->src[begin] == q)
			return (1);
		begin++;
	}
	return (0);
}
