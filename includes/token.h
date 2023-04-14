/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:43:32 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/14 15:33:27 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>

typedef enum s_tokens_type
{
	PIPE = 1, // |
	GREAT_THAN,// >
	LESS_THAN, // <
	HEREDOC, // <<
	APPEND, // >>
}	t_tokens_type;

typedef struct s_tokens
{
	char			*str;
	t_tokens_type	type;
}	t_token;


// function to initialize the tokens
t_token		*init_tokens(char *str, int type);

#endif
