/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/21 13:47:38 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	ff(t_parser *tmp)
{
	free(tmp->current_token->val);
	free(tmp->previous_token->val);
}
/* Check PIPE syntax */
int	pipe_syntax(t_parser *parser, char *cmd)
{
	(void)cmd;
	printf("in PIPE current = %s\n", parser->current_token->val);
	while (parser->current_token->type != t_EOF)
	{
		if (parser->current_token->type == t_PIPE)
		{
			g_gob.nb_cmd++;
			if (parser->previous_token == NULL)
			{
				parser->lexer->i = 0;
				parser->lexer->c = parser->lexer->src[parser->lexer->i];
				ff(parser);
				return (1);
			}
			else if (parser->previous_token->type == t_PIPE
					|| type_is_rederec(parser->previous_token) == 0)
			{
				parser->lexer->i = 0;
				parser->lexer->c = parser->lexer->src[parser->lexer->i];
				return (1);
			}
		}
		parser->previous_token = parser->current_token;
		free(parser->current_token);
		parser->current_token = get_next_token(parser->lexer);
		if (parser->current_token->type == t_EOF
			&& parser->previous_token->type == t_PIPE)
		{
			parser->lexer->i = 0;
			parser->lexer->c = parser->lexer->src[parser->lexer->i];
			return (1);
		}
	}
	parser->lexer->i = 0;
	parser->lexer->c = parser->lexer->src[parser->lexer->i];
	return (0);
}

/* Check redirection syntax */
int	redirect_syntax(t_parser *parser, char *cmd)
{
	(void)cmd;
	printf("in redrct = %d\n", parser->current_token->type);
	while (parser->current_token->type != t_EOF)
	{
		if (parser->current_token->type == t_GREAT_THAN
			|| parser->current_token->type == t_LESS_THAN)
		{
			if (parser->previous_token
				&& (parser->previous_token->type == t_GREAT_THAN
					|| parser->previous_token->type == t_LESS_THAN))
			{
				parser->lexer->i = 0;
				parser->lexer->c = parser->lexer->src[parser->lexer->i];
				return (1);
			}
		}
		else if (parser->current_token->type == t_HEREDOC
				|| parser->current_token->type == t_APPEND)
		{
			if (!parser->previous_token
				|| parser->previous_token->type == t_GREAT_THAN
				|| parser->previous_token->type == t_LESS_THAN)
			{
				parser->lexer->i = 0;
				parser->lexer->c = parser->lexer->src[parser->lexer->i];
				return (1);
			}
		}
		parser->previous_token = parser->current_token;
		free(parser->current_token);
		parser->current_token = get_next_token(parser->lexer);
		if (parser->current_token->type == t_EOF
			&& type_is_rederec(parser->previous_token) == 0)
		{
			parser->lexer->i = 0;
			parser->lexer->c = parser->lexer->src[parser->lexer->i];
			return (1);
		}
	}
	parser->lexer->i = 0;
	parser->lexer->c = parser->lexer->src[parser->lexer->i];
	return (0);
}

int	iterate_over_tokens_check_syntaxe(t_parser *parser, char *cmd)
{
	if ((pipe_syntax(parser, cmd) == 1) || (redirect_syntax(parser, cmd) == 1))
		return (err_msg("Bash : syntax error"));
	return (0);
}