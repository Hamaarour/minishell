/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:36 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/23 21:37:01 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/**
strerror() is a standard library function that returns a string description of the error code
stored in errno.
In summary, errno is a global variable that stores error codes,
	and strerror() is a standard library function
that can be used to convert those error codes into human-readable error messages
*/
char	*exit_value(t_lexer *lexer)
{
	char	*val;

	val = ft_itoa(glob.ex_status);
	if (val == NULL)
		error_func(errno);
	advance_lexer(lexer);
	return (val);
}

/*
	get the string between double qoutes  " "   and return it
	
*/
char	*double_quote(t_lexer *lexer)
{
	char	*string;

	advance_lexer(lexer);
	if (!check_qutes(lexer, '"'))
	{
		ft_putendl_fd("Bash Error : \"Quotes\"", 2);
		glob.ex_status = 258;
		return (NULL);
	}
	string = ft_strdup("");
	while (lexer->c != '"' && lexer->c != '\0')
	{
		if (lexer->c == '$')
			expand_dollar(lexer, &string);
		else
			get_string_between_double_qoutes(lexer, &string);
	}
	advance_lexer(lexer);
	return (string);
}

/*
	get the string between single qoutes and double qoutes and return it    
*/
char	*hundle_quotes(t_lexer *lexer)
{
	char	*tmp;

	if (lexer->c == '\'')
		tmp = single_quote(lexer);
	else
		tmp = double_quote(lexer);
	return (tmp);
}

/*
	get the string between double qoutes and single qoutes and return it
*/
char	*get_dollar(t_lexer *lexer)
{
	char *tmp; //str
	char *str; //s
	str = ft_strdup("");
	advance_lexer(lexer);
	if (lexer->c == '?')
	{
		glob.ex_status = 1;
		tmp = exit_value(lexer);
	}
	else if (lexer->c == '\"' || lexer->c == '\'')
		tmp = hundle_quotes(lexer);
	else
		tmp = envairment_var(lexer);
	if (tmp == NULL)
		return (NULL);
	str = ft_strjoin(str, tmp);
	if (ft_strlen(tmp) >= 0)
		free(tmp);
	if (str == NULL)
		error_func(errno);
	return (str);
}
