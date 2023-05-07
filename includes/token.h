/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:43:32 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/07 17:55:17 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>

typedef enum s_tokens_type
{
	t_CHAR, // any word
	t_PIPE , // |
	t_GREAT_THAN,// >
	t_LESS_THAN, // <
	t_HEREDOC, // <<
	t_APPEND, // >>
	t_EOF, // end of file
	TOKEN_EXIT, // $? exit status
}	t_tokens_type;

typedef struct s_tokens
{
	t_tokens_type	type;
	char			*val;

}	t_token;

// function to initialize the tokens
t_token	*init_tokens(t_tokens_type typ, char *val);

#endif

