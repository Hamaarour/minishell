/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:52:37 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/21 13:55:52 by hamaarou         ###   ########.fr       */
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

	lexer = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->src = src;
	lexer->i = 0;
	lexer->c = src[lexer->i];
	lexer->len_src = ft_strlen(src);
	return (lexer);
}

/*
	the advance_lexer function advances the lexer to the next character in the source
	string, updating the i and c members of the lexer object accordingly,
		as long as
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

/*
	The lexer_advance_with_token function is used to advance the lexer to the next
	character in the source string,
		and return a token object. It takes a pointer to
	a t_lexer object and a pointer to a t_token object as input,
		and returns a pointer
	to a t_token object.
*/
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	advance_lexer(lexer);
	return (token);
}

/*
	get the next token 
*/

t_token	*advance_to_next_tocken(t_lexer *lexer, t_token *token)
{
	advance_lexer(lexer);
	return (token);
}