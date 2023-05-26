/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:10:16 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/26 23:08:01 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/*
	The lexer_skip_whitespace function is used to skip over any whitespace characters
	in the source string. It takes a pointer to a t_lexer object as input,
		and returns
	void.
*/
void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
		advance_lexer(lexer);
}

/*
This is a function  takes in a pointer to a t_lexer 
struct and returns a pointer to a t_token struct. This function is called 
when the current character being examined by the lexer is not a space, tab, |,
	>, or <,
 indicating that the current character is part of a string.
*/
t_token	*fetch_string(t_lexer *lexer)
{
	char	*tmp;

	char *str; //str is the string that will be returned
	//tmp is a temporary string that will be used to store the characters of the word
	str = ft_strdup("");
	tmp = NULL;
	while (lexer->c != '<' && lexer->c != '>' && lexer->c != '|'
		&& lexer->c != '\t' && lexer->c != ' ' && lexer->c != '\0')
	{
		if (lexer->c == '\'')
		{
			tmp = single_quote(lexer);
		}
		else if (lexer->c == '"')
			tmp = double_quote(lexer);
		else if (lexer->c == '$')
			tmp = get_dollar(lexer);
		else
			tmp = get_char(lexer);
		if (tmp == NULL)
		{
			if (str)
				free(str);
			return (NULL);
		}
		str = ft_strjoin(str, tmp);
		free(tmp);
		if (!str)
			return (NULL);
		//error_func(errno);
	}
	return (init_tokens(t_CHAR, str));
}

/*
The lexer, also called the tokenizer, takes as the entered line as input.
It then reads through the line word by word, using white space as delimiters.
First it checks wether or not the word is a token, ie: |, <, <<, >, or >>,
	This is a function in a lexer program that takes in a pointer to a t_lexer struct and 
	returns a pointer to a t_token struct. The t_lexer struct contains information about 
	the source code being lexed,
		such as the current character being examined and the index 
	of the character within the source code. The t_token struct represents a token
	which is a unit of meaningful information in the source code.
	The purpose of this function is to scan the source code and return the next token.
*/
t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespace(lexer);
		else if (lexer->c == '|')
			return (advance_to_next_tocken(lexer, init_tokens(t_PIPE,
						ft_strdup("|"))));
		else if (lexer->c == '>')
			return (rederection_great(lexer));
		else if (lexer->c == '<')
			return (rederection_less(lexer));
		else if (lexer->c != ' ' && lexer->c != '\t')
			return (fetch_string(lexer));
	}
	return (init_tokens(t_EOF, ft_strdup("EOF")));
}
