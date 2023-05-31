/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:51:19 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/31 17:23:28 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	cleanup_parser(t_parser *parser)
{
	if (parser->lexer != NULL)
	{
		free(parser->lexer->src);
		free(parser->lexer);
		parser->lexer = NULL;
	}
	if (parser->current_token != NULL)
	{
		free(parser->current_token->val);
		free(parser->current_token);
		parser->current_token = NULL;
	}
	if (parser->previous_token != NULL)
	{
		free(parser->previous_token->val);
		free(parser->previous_token);
		parser->previous_token = NULL;
	}
	free(parser);
}

void	free_arg(t_args *arg)
{
	free(arg->args);
	free(arg);
}

void	free_prev(t_parser *parser)
{
	if (parser->previous_token)
	{
		free(parser->previous_token->val);
		free(parser->previous_token);
		parser->previous_token = NULL;
	}
}
