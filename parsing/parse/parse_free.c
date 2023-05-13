/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:51:19 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/13 21:42:06 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	parser_free(t_parser *parser)
{
	if (parser != NULL)
	{
		if (parser->lexer != NULL)
		{
			free(parser->lexer->src);
			free(parser->lexer);
		}
		if (parser->previous_token)
			free_tocken(parser->previous_token);
		if (parser->current_token)
			free_tocken(parser->current_token);
		if (parser)
			free(parser);
	}
}