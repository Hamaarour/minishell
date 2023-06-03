/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:36 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/03 11:02:28 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

//strerror() is a standard library function that returns a string 
//description of the error codestored in errno.
//In summary, errno is a g_global variable that stores error codes,
//	and strerror() is a standard library function
//that can be used to convert those error codes into human-readable
// error messages

char	*exit_value(t_lexer *lexer)
{
	char	*val;

	val = ft_itoa(lexer->ex_status);
	if (val == NULL)
		error_func(errno);
	advance_lexer(lexer);
	return (val);
}

char	*double_quote(t_lexer *lexer, int flag)
{
	char	*string;

	advance_lexer(lexer);
	g_glob.to_expand = 1;
	if (!check_qutes(lexer, '"'))
	{
		ft_putendl_fd("Bash Error : \"Quotes\"", 2);
		g_glob.ex_status = 258;
		return (NULL);
	}
	string = ft_strdup("");
	while (lexer->c != '"' && lexer->c != '\0')
	{
		if (lexer->c == '$' && flag == 0)
			expand_dollar(lexer, &string);
		else
			get_string_between_double_qoutes(lexer, &string, flag);
	}
	advance_lexer(lexer);
	return (string);
}

char	*hundle_quotes(t_lexer *lexer, int flag)
{
	char	*tmp;

	if (lexer->c == '\'')
		tmp = single_quote(lexer);
	else
		tmp = double_quote(lexer, flag);
	return (tmp);
}

char	*get_dollar(t_lexer *lexer, int flag)
{
	char	*tmp;
	char	*str;

	str = ft_strdup("");
	advance_lexer(lexer);
	if (lexer->c == '?')
	{
		tmp = exit_value(lexer);
	}
	else if (lexer->c == '\"' || lexer->c == '\'')
		tmp = hundle_quotes(lexer, flag);
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
