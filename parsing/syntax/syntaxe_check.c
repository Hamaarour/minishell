/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/24 23:26:42 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

int	check_II(t_token *current, t_token *previous)
{
	if ((current->type == t_LESS_THAN || current->type == t_GREAT_THAN)
		&& (previous->type == t_APPEND || previous->type == t_HEREDOC))
		return (0);
	return (1);
}

void	reinitialize_parser(t_parser *parser)
{
	//free(parser->previous_token);
	parser->lexer->i = 0;
	parser->lexer->c = parser->lexer->src[parser->lexer->i];
	free(parser->current_token);
	free(parser->previous_token);
	parser->current_token = get_next_token(parser->lexer);
	parser->previous_token = NULL;
}

/* Check PIPE syntax */
int	pipe_syntax(t_parser *parser)
{
	while (parser->current_token->type != t_EOF)
	{
		if (parser->previous_token != NULL)
		{
			if ((type_out_in(parser->previous_token) == 0
					|| parser->previous_token->type == t_APPEND)
				&& ft_strlen(parser->current_token->val) == 0)
				parser->lexer->ambg_redir++;
		}
		if (parser->current_token->type == t_PIPE)
		{
			glob.nb_cmds++;
			if (parser->previous_token == NULL)
				return (reinitialize_parser(parser), 1);
			else if (parser->previous_token->type == t_PIPE
					|| type_is_rederec(parser->previous_token) == 0)
				return (reinitialize_parser(parser), 1);
		}
		parser->previous_token = parser->current_token;
		parser->current_token = get_next_token(parser->lexer);
		if (parser->current_token->type == t_EOF
			&& parser->previous_token->type == t_PIPE)
			return (reinitialize_parser(parser), 1);
	}
	return (reinitialize_parser(parser), 0);
}

/* Check redirection syntax */
int	redirect_syntax(t_parser *parser)
{
	while (parser->current_token->type != t_EOF)
	{
		if (type_out_in(parser->current_token) == 0)
		{
			if (parser->previous_token
				&& (type_out_in(parser->previous_token) == 0
					|| check_II(parser->current_token,
						parser->previous_token) == 0))
				return (reinitialize_parser(parser), 1);
		}
		else if (type_hd_apd(parser->current_token) == 0)
		{
			if (!parser->previous_token
				|| (type_out_in(parser->previous_token) == 0))
				return (reinitialize_parser(parser), 1);
		}
		parser->previous_token = parser->current_token;
		parser->current_token = get_next_token(parser->lexer);
		if (parser->current_token->type == t_EOF
			&& type_is_rederec(parser->previous_token) == 0)
			return (reinitialize_parser(parser), 1);
	}
	return (reinitialize_parser(parser), 0);
}

int	iterate_over_tokens_check_syntaxe(t_parser *parser)
{
	if ((pipe_syntax(parser) == 1) || (redirect_syntax(parser) == 1))
	{
		return (err_msg("Bash : syntax error"));
	}
	return (0);
}