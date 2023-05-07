/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:10:16 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/07 18:09:29 by hamaarou         ###   ########.fr       */
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

	lexer = (t_lexer *)ft_calloc(1,sizeof(t_lexer));
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
/*
	The lexer_skip_whitespace function is used to skip over any whitespace characters
	in the source string. It takes a pointer to a t_lexer object as input, and returns
	void.
*/
void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
		advance_lexer(lexer);
}
/*
	The lexer_advance_with_token function is used to advance the lexer to the next
	character in the source string, and return a token object. It takes a pointer to
	a t_lexer object and a pointer to a t_token object as input, and returns a pointer
	to a t_token object.
*/
t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	advance_lexer(lexer);
	return (token);
} 
/*
This is a function  takes in a pointer to a t_lexer 
struct and returns a pointer to a t_token struct. This function is called 
when the current character being examined by the lexer is not a space, tab, |, >, or <,
 indicating that the current character is part of a string.
*/
t_token	*fetch_string(t_lexer *lexer)
{
	char	*str;//str is the string that will be returned
	char	*tmp;//tmp is a temporary string that will be used to store the characters of the word

	str = ft_strdup("");
	tmp = NULL;
	while (lexer->c != '<' && lexer->c != '>' && lexer->c != '|' 
		&& lexer->c != '\t' && lexer->c != ' ' && lexer->c != '\0')
	{
		if (lexer->c == '$')
		{
			tmp = get_dollar(lexer);
		}
		else if (lexer->c == '\'')
			tmp = single_quote(lexer);
		else if (lexer->c == '"')
			tmp = hundle_quotes(lexer);		
		else
			tmp = get_char(lexer);
		
		str = ft_strjoin(str, tmp);
		printf("part = %s\n", str);
		free(tmp);
		if (!str)
			error_func(errno);
	}
	printf("*** joined = %s***\n", str);
	return (init_tokens(t_CHAR, str));
}
/*
The lexer, also called the tokenizer, takes as the entered line as input.
It then reads through the line word by word, using white space as delimiters.
First it checks wether or not the word is a token, ie: |, <, <<, >, or >>,
	This is a function in a lexer program that takes in a pointer to a t_lexer struct and 
	returns a pointer to a t_token struct. The t_lexer struct contains information about 
	the source code being lexed, such as the current character being examined and the index 
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
			return (lexer_advance_with_token(lexer, init_tokens(t_PIPE, ft_strdup("|"))));
		else if (lexer->c == '>')
		{
			//	condition to check if the next character is also a >, if so, return a token with type t_APPEND and value ">>"
			if(lexer->src[lexer->i + 1] == '>')
				return (lexer_advance_with_token(lexer, init_tokens(t_APPEND, ft_strdup(">>"))));
			return (lexer_advance_with_token(lexer, init_tokens(t_GREAT_THAN, ft_strdup(">"))))	;
		}
		else if (lexer->c == '<')
		{
			//	condition to check if the next character is also a <, if so, return a token with type t_HEREDOC and value "<<"
			if (lexer->src[lexer->i + 1] == '<')
				return (lexer_advance_with_token(lexer, init_tokens(t_HEREDOC, ft_strdup("<<"))));
			return (lexer_advance_with_token(lexer, init_tokens(t_LESS_THAN, ft_strdup("<"))));
		}
		else if (lexer->c != ' ' && lexer->c != '\t')
			fetch_string(lexer);
	}
	return (init_tokens(t_EOF, ft_strdup("EOF")));
}
