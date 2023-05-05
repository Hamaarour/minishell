/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:36 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/04 19:45:10 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/**
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

/*
+ The function checks whether the quotes in the string are balanced 
	or not. 
*/

char	*single_quote(t_lexer *lexer)
{
	char	*tmp;
	int 	begin;
	int		end;
	advance_lexer(lexer);
	begin = lexer->i;
	if(check_qutes(lexer->src, '\'') == 1)
	{
		lexer->ex_status = 450;
		return (NULL);
	}
	while (lexer->c != '\'' && lexer->c != '\0')
		advance_lexer(lexer);
	end = lexer->i;
	tmp = ft_substr(lexer->src, begin, end - begin);
	if (tmp == NULL)
		error_func(errno);
	advance_lexer(lexer);
	return (tmp);
}

char	*envairment_var(t_lexer *lexer)
{
	char	*str;
	int 	begin;
	int		end;

	begin = lexer->i;
	while (ft_isalnum(lexer->c))
		advance_lexer(lexer);
	end = lexer->i;
	str = ft_substr(lexer->src, begin, end - begin);
	//add here an error function if str == NULL
	if(str == NULL)
		error_func(errno);
	str = get_envairment_var(str);
	if (str == NULL)
		str = ft_strdup("");
	return (str);
}

char	*expand_dollar(t_lexer *lexer)
{
	char	*tmp;
	char	*str;

	advance_lexer(lexer);
	if (lexer->c == '?')
		tmp = exit_value(lexer);
	else
		tmp = envairment_var(lexer);
	
}

char	*double_quote(t_lexer *lexer)
{
	char	*tmp;

	advance_lexer(lexer);
	if(check_qutes(lexer->src, '"') == 1)
	{
		lexer->ex_status = 450;
		return (NULL);
	}
	while (lexer->c != '"' && lexer->c != '\0')
	{
		if (lexer->c == '$')
				tmp = expand_dollar(lexer);
		else
			
	}
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
		tmp = exit_value(lexer);
	else if (lexer->c == '\"' || lexer->c == '\'')
		tmp = hundle_quotes(lexer);
	else
		tmp = get_string(lexer);
}
