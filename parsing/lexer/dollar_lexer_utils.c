/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_lexer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:57:46 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/22 04:31:17 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/*
+ The function checks whether the quotes in the string are balanced 
	or not. 
*/
char	*single_quote(t_lexer *lexer)
{
	char	*tmp;
	int		begin;
	int		end;

	advance_lexer(lexer);
	begin = lexer->i;
	if (check_qutes(lexer->src, '\'') == 1)
	{
		glob.ex_status = 258;
		return (NULL);
	}
	while (lexer->c != '\'' && lexer->c != '\0')
		advance_lexer(lexer);
	end = lexer->i;
	tmp = ft_substr_p(lexer->src, begin, end - begin);
	if (tmp == NULL)
		error_func(errno);
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
	int		begin;
	int		end;
	char	*tmp;

	// another pointer to free the str after the get_envairment_var function
	begin = lexer->i;
	while (ft_isalnum(lexer->c))
		advance_lexer(lexer);
	end = lexer->i;
	str = ft_substr_p(lexer->src, begin, end - begin);
	tmp = str;
	if (str == NULL)
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
	int	begin;
	int	end;

	char *string_btw_dq; //string between double qoutes
	begin = lexer->i;
	while (lexer->c != '$' && lexer->c != '"' && lexer->c != '\0')
		advance_lexer(lexer);
	end = lexer->i;
	string_btw_dq = ft_substr_p(lexer->src, begin, end - begin);
	if (string_btw_dq == NULL)
		error_func(errno);
	*my_str = ft_strjoin(*my_str, string_btw_dq);
	free(string_btw_dq);
	//add here an error function if my_str == NULL
}
