/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/11 19:25:39 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	type_is_rederec(t_token *token)
{
	if (token)
	{
		if (token->type == t_GREAT_THAN || token->type == t_LESS_THAN 
			|| token->type == t_HEREDOC|| token->type == t_APPEND)
			return (0);
	}
	return (1);
}

int syntaxe_check(t_parser *parser)
{
	if(parser->current_token != NULL)
	{
		if(parser->current_token->type == t_PIPE || parser->current_token->type == t_EOF)
		{
			// expected is a T_CHAR
			if (parser->current_token)
			{
				if (parser->current_token->type == t_CHAR)
				{
					
				}
				else
				{
					// syntaxe error
					return (258);
				}
			}
		}
	}
}
