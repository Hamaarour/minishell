/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:24:22 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/03 16:00:55 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/*
	The get_char function is used to get a single character from the source string.
	It takes a pointer to a t_lexer object as input, and returns a pointer to a
	character array containing the character.
*/
char	*get_char(t_lexer *lexer, int flag)
{
	char	*tmp;
	int		begin;
	int		end;

	begin = lexer->i;
	if (flag == 0)
	{
		while (lexer->c != '<' && lexer->c != '>' && lexer->c != '|'
			&& lexer->c != '\t' && lexer->c != ' ' && lexer->c != '"'
			&& lexer->c != '\0' && lexer->c != '\'' && lexer->c != '$')
			advance_lexer(lexer);
	}
	else
	{
		while (lexer->c != '<' && lexer->c != '>' && lexer->c != '|'
			&& lexer->c != '\t' && lexer->c != ' ' && lexer->c != '\0')
			advance_lexer(lexer);
	}
	end = lexer->i;
	tmp = ft_substr_p(lexer->src, begin, end - begin);
	if (tmp == NULL)
		error_func(errno);
	return (tmp);
}
