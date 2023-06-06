/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/06 17:44:08 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

int	pipe_utils(t_parser *parser)
{
	if (parser->previous_token)
	{
		free(parser->previous_token->val);
		free(parser->previous_token);
	}
	parser->previous_token = parser->current_token;
	parser->current_token = get_next_token(parser->lexer, 0);
	if (parser->current_token == NULL)
		return (free_it_ii(parser), 1);
	if (parser->current_token->type == t_EOF
		&& parser->previous_token->type == t_PIPE)
		return (free_it(parser), 1);
	return (0);
}

int	pipe_syntax(t_parser *parser)
{
	g_glob.nb_cmds = 1;
	while (parser->current_token->type != t_EOF)
	{
		if (parser->previous_token != NULL)
		{
			if ((type_out_in(parser->previous_token) == 0
					|| parser->previous_token->type == t_APPEND)
				&& ft_strlen(parser->current_token->val) == 0)
				g_glob.ambg_redir++;
		}
		if (parser->current_token != NULL
			&& parser->current_token->type == t_PIPE)
		{
			g_glob.nb_cmds++;
			if (parser->previous_token == NULL)
				return (free_it(parser), 1);
			else if (parser->previous_token->type == t_PIPE
				|| type_is_rederec(parser->previous_token) == 0)
				return (free_it(parser), 1);
		}
		if (pipe_utils(parser) == 1)
			return (1);
	}
	return (reinitialize_parser(parser), 0);
}

int	redirect_utils(t_parser *parser)
{
	if (parser->previous_token)
	{
		free(parser->previous_token->val);
		free(parser->previous_token);
	}
	parser->previous_token = parser->current_token;
	parser->current_token = get_next_token(parser->lexer, 0);
	if (parser->current_token == NULL)
		return (free_it_ii(parser), 1);
	if (parser->current_token->type == t_EOF
		&& type_is_rederec(parser->previous_token) == 0)
		return (free_it(parser), 1);
	return (0);
}

int	redirect_syntax(t_parser *parser)
{
	while (parser->current_token->type != t_EOF)
	{
		if (parser->previous_token != NULL)
		{
			if (type_out_in(parser->current_token) == 0)
			{
				if ((type_out_in(parser->previous_token) == 0
						|| check_ii(parser->current_token,
							parser->previous_token) == 0))
					return (free_it(parser), 1);
			}
			if (type_hd_apd(parser->current_token) == 0)
			{
				if (!parser->previous_token
					|| (type_out_in(parser->previous_token) == 0)
					|| type_hd_apd(parser->previous_token) == 0)
					return (free_it(parser), 1);
			}
		}
		if (redirect_utils(parser) == 1)
			return (1);
	}
	return (reinitialize_parser(parser), 0);
}

int	iterate_over_tokens_check_syntaxe(t_parser *parser)
{
	if ((pipe_syntax(parser) == 1) || (redirect_syntax(parser) == 1))
	{
		err_msg("\033[1;31mBash : syntax error\033[1;0m");
		return (1);
	}
	return (42);
}
