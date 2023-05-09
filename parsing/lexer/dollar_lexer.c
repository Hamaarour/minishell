/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:36 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/09 21:04:37 by hamaarou         ###   ########.fr       */
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
	(void)lexer;
	val = ft_itoa(g_gob.ex_status);
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
		g_gob.ex_status = 258;
		return (NULL);
	}
	while (lexer->c != '\'' && lexer->c != '\0')
		advance_lexer(lexer);
	end = lexer->i;
	tmp = ft_substr(lexer->src, begin, end - begin);
	// if (tmp == NULL)
	// 	error_func(errno);
	advance_lexer(lexer);
	return (tmp);
}

/*
	the envairment var is the var that we can find in the envairment
	variables like HOME, USER, PATH, etc...
*/
char	*envairment_var(t_lexer *lexer)
{
	char	*str;
	char	*tmp;// another pointer to free the str after the get_envairment_var function
	int 	begin;
	int		end;

	begin = lexer->i;
	while (ft_isalnum(lexer->c))
		advance_lexer(lexer);
	end = lexer->i;
	str = ft_substr(lexer->src, begin, end - begin);
	printf("str = %s\n", str);
	tmp = str;
	if(str == NULL)
		error_func(errno);
	str = get_envairment_var(tmp, lexer);
	if (str == NULL)
		str = ft_strdup("");
	free(tmp);
	return (str);
}

/*
	expand the string next to  $ with three cases :
	1) $_ || ${isalpha} search in envairment variables
	2) the opposit of case 1
	3) $? the exit status of the last command
*/
void	expand_dollar(t_lexer *lexer, char **my_str)
{
	char	*tmp;

	advance_lexer(lexer);
	if (lexer->c == '?')
		tmp = exit_value(lexer);
	else
		tmp = envairment_var(lexer);
	*my_str = ft_strjoin(*my_str, tmp);
	free(tmp);
	
	//add here an error function if my_str == NULL
}


/*
	get the string between double qoutes  " "   and return it
*/
void	get_string_between_double_qoutes(t_lexer *lexer, char **my_str)
{
	int		begin;
	int		end;
	char	*string_btw_dq;//string between double qoutes

	begin = lexer->i;
	while (lexer->c != '$' && lexer->c != '"' && lexer->c != '\0')
		advance_lexer(lexer);
	end = lexer->i;
	string_btw_dq = ft_substr(lexer->src, begin, end - begin);
	if (string_btw_dq == NULL)
		error_func(errno);
	*my_str = ft_strjoin(*my_str, string_btw_dq);
	free(string_btw_dq);
	//add here an error function if my_str == NULL
}


/*
	get the string between double qoutes  " "   and return it
	
*/
char	*double_quote(t_lexer *lexer)
{
	char	*string;

	advance_lexer(lexer);
	if(check_qutes(lexer->src, '"') == 1)
	{
		g_gob.ex_status = 258;
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
	char	*tmp; //str
	char	*str; //s

	str = ft_strdup("");
	advance_lexer(lexer);
	if (lexer->c == '?')
		tmp = exit_value(lexer);
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
