/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:36 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/03 22:10:27 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
strerror() is a standard library function that returns a string description of the error code
stored in errno.
In summary, errno is a global variable that stores error codes, and strerror() is a standard library function
that can be used to convert those error codes into human-readable error messages
*/

char	*exit_value(t_lexer *lexer)
{
	char	*val;

	val = ft_itoa(lexer->ex_status);
	if (val == NULL)
		error_func(errno);
	return (val);
}
char	*hundle_quotes(t_lexer *lexer)
{
	char	*tmp;

	if (lexer->c == '\'')
		tmp = single_quote(lexer);
	else
		tmp = double_quote(lexer);

	return (tmp);
}

t_lexer *get_dollar(t_lexer *lexer)
{
	char	*tmp; //str
	char	*str; //s

	int	begin;
	advance_lexer(lexer);

	begin = lexer->i;
	if (lexer->c == '?')
	{
		// exit_value() return the value of exist status
		tmp = exit_value(lexer);
	}
	else if (lexer->c == '\"' || lexer->c == '\'')
	{
		// hundle_quotes() return the string between the quotes
		tmp = hundle_quotes(lexer);
	}
	else
	{
		// get_string() return the string between the quotes
		tmp = get_string(lexer);
	}

	while (ft_isalnum(lexer->c))
		advance_lexer(lexer);


}
