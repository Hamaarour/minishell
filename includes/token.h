/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:43:32 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/12 16:37:17 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>

typedef enum s_tokens_type
{
	t_CHAR, // any word 0
	t_PIPE , // | 1
	t_GREAT_THAN,// > 2
	t_LESS_THAN, // < 3
	t_HEREDOC, // << 4
	t_APPEND, // >> 5
	t_EOF, // end of file 6 
}	t_tokens_type;

typedef struct s_tokens
{
	t_tokens_type	type;
	char			*val;

}	t_token;

// function to initialize the tokens
t_token	*init_tokens(t_tokens_type typ, char *val);

#endif


