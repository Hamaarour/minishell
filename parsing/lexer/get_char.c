/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:24:22 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/07 17:56:34 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
	The get_char function is used to get a single character from the source string.
	It takes a pointer to a t_lexer object as input, and returns a pointer to a
	character array containing the character.
*/
char	*get_char(t_lexer *lexer)
{
	char	*tmp;
	int		begin;
	int		end;

	begin = lexer->i;
	while (lexer->c != '<' && lexer->c != '>' && lexer->c != '|' 
			&& lexer->c != '\t' && lexer->c != ' ' && lexer->c != '"'
			&& lexer->c != '\0' && lexer->c != '\'' && lexer->c != '$')
		advance_lexer(lexer);
	end = lexer->i;
	tmp = ft_substr(lexer->src, begin, end - begin);
	if (tmp == NULL)
		error_func(errno);
	return (tmp);
}

