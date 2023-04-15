/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:36:34 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/15 00:35:56 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
src: a pointer to a character array that represents
	the source string to be tokenized.
c: a character that represents the current character
	being processed in the source string.
i: an integer that represents the index of the current
	character in the source string
len_src: an integer that represents the length of the source string
*/
typedef struct s_lexer
{
	char				*src;
	char				c;
	unsigned int		i;
	size_t				len_src;
}	t_lexer;

t_lexer	*init_lexer(char *str);
void	advance_lexer(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
#endif
