/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:27:39 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/31 16:31:36 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	free_it(t_parser *parser)
{
	free(parser->lexer->src);
	free(parser->lexer);
	free(parser->current_token->val);
	free(parser->current_token);
	if (parser->previous_token != NULL)
	{
		free(parser->previous_token->val);
		free(parser->previous_token);
	}
	free(parser);
}

void	free_it_ii(t_parser *parser)
{
	if (parser->current_token)
	{
		free(parser->current_token->val);
		free(parser->current_token);
	}
	if (parser->previous_token)
	{
		free(parser->previous_token->val);
		free(parser->previous_token);
	}
	free(parser->lexer->src);
	free(parser->lexer);
	free(parser);
}

int	check_ii(t_token *current, t_token *previous)
{
	if ((current->type == t_LESS_THAN || current->type == t_GREAT_THAN)
		&& (previous->type == t_APPEND || previous->type == t_HEREDOC))
		return (0);
	return (1);
}

void	reinitialize_parser(t_parser *parser)
{
	parser->lexer->i = 0;
	parser->lexer->c = parser->lexer->src[parser->lexer->i];
	if (parser->current_token)
	{
		free(parser->current_token->val);
		free(parser->current_token);
	}
	if (parser->previous_token)
	{
		free(parser->previous_token->val);
		free(parser->previous_token);
	}
	parser->current_token = get_next_token(parser->lexer);
	if (parser->current_token == NULL)
	{
		return ;
	}
	parser->previous_token = NULL;
}
