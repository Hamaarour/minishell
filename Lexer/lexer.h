/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:43:32 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/13 16:46:49 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>

typedef enum s_tokens
{
	PIPE = 1,
	GREAT_THAN,
	HEREDOC,
	LESS_THAN,
	APPEND,
}	t_tokens;


#endif
