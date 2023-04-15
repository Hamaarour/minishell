/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:10:16 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/15 01:04:31 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
	The init_lexer function is used to initialize a t_lexer object.
	It takes a pointer to a character array (src) as input, which
	represents the source string to be tokenized.

	The src pointer is then assigned to the src member of the lexer object,
	 and the first character of the source string (src[lexer->i]) is assigned
	 to the c member of the lexer object. The i member is initialized to 0.
*/
t_lexer	*init_lexer(char *src)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->src = src;
	lexer->c = src[lexer->i];
	lexer->i = 0;
	lexer->len_src = ft_strlen(src);
	return (lexer);
}
/*
	the advance_lexer function advances the lexer to the next character in the source
	string, updating the i and c members of the lexer object accordingly, as long as
	there are more characters in the source string and the current character is not
	the end of the string.
*/
void	advance_lexer(t_lexer *lexer)
{
	if (lexer->i < lexer->len_src && lexer->c != '\0')
	{
		lexer->i++;
		lexer->c = lexer->src[lexer->i];
	}
}

t_token	*get_next_token(t_lexer *lexer)
{

}

