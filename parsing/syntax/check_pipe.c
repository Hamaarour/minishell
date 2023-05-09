/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:10 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/09 12:38:48 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
/*
+ We initialize {len} to the length of the input string using the ft_strlen() function.
+ We initialize {prev_pipe} to 0, which will be used to keep track of whether the previous
+	character was a pipe character.
+ We initialize {printed_error} to 0, which will be used to keep track
+	of whether we have already printed a syntax error message.
*/
/*
	-We first check if the first or last character of the input string is a pipe character.
	-If it is, we print a syntax error message using printf() and set printed_error to 1 to
	-indicate that we have already printed an error message

	-is_pipe_valid: This function takes in a character array and an index, and checks whether
	-the character at that index is a valid pipe character. It returns a boolean value indicating
	-whether the character is a valid pipe or not.

	-check_initial_and_final_pipes: This function takes in a lexer struct, and checks whether the first
	-	or last character of the string in the struct is a pipe character. If either is a pipe character,
	-	it prints a syntax error message.

	-check_consecutive_pipes: This function takes in a lexer struct, and checks for consecutive pipe
	-	characters in the string. If it finds consecutive pipes, it prints a syntax error message. If it
	-	encounters the first pipe character, it sets a flag to indicate that the previous character was
	-	a pipe, and checks subsequent characters to see if they are also pipe characters. If it encounters
	-	a non-pipe character, it resets the flag.
 */

void	check_pipe_begin_end(t_str *lex)
{
	int	len;

	len = ft_strlen(lex->str);
	if (lex->str[0] == '|' || lex->str[len - 1] == '|')
	{
		ft_putendl_fd("Error: Syntax error", 2);
		lex->printed_error = 1;
	}
}

void	check_pipe_repeated(t_str *lex)
{
	unsigned int	i;
	int				prev_pipe;

	i = 0;
	prev_pipe = 0;
	while (i < ft_strlen(lex->str))
	{
		if (lex->str[i] == '|')
		{
			if (prev_pipe)
			{
				if (!lex->printed_error)
				{
					ft_putendl_fd("Error: Syntax error", 2);
					lex->printed_error = 1;
				}
			}
			prev_pipe = 1;
		}
		else
			prev_pipe = 0;
		i++;
	}
}

void	check_pipe_space(t_str *lex)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < ft_strlen(lex->str))
	{
		if (lex->str[i] == '|')
		{
			j = i + 1;
			while (j < ft_strlen(lex->str)
				&& (lex->str[j] == ' ' || lex->str[j] == '\t'))
				j++;
			if (j < ft_strlen(lex->str) && lex->str[j] == '|')
			{
				if (!lex->printed_error)
				{
					ft_putendl_fd("Error: Syntax error", 2);
					lex->printed_error = 1;
				}
			}
		}
		i++;
	}
}

void	check_pipes(t_str *lex)
{
	lex->printed_error = 0;
	check_pipe_begin_end(lex);
	check_pipe_repeated(lex);
	check_pipe_space(lex);
}
