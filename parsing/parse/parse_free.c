/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:51:19 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/22 02:06:31 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	token_free(t_token *tocken)
{
	if (tocken != NULL)
	{
		if (tocken->type != t_CHAR)
		{
			if (tocken->val)
				free(tocken->val);
		}
		if (tocken)
			free(tocken);
	}
}

/* free a parser */

void	free_parser_final(t_parser *parser)
{
	if (parser != NULL)
	{
		if (parser->lexer != NULL)
		{
			free(parser->lexer->src);
			free(parser->lexer);
		}
		if (parser->previous_token)
			token_free(parser->previous_token);
		if (parser->current_token)
			token_free(parser->current_token);
		if (parser)
			free(parser);
	}
}