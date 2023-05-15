/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/15 01:13:44 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int type_is_char(t_token *token)
{
	if (token)
	{
		if (token->type == t_CHAR)
			return (0);
	}
	return (1);
}

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

int	type_is_pipe(t_token *token)
{
	if (token)
	{
		if (token->type == t_PIPE)
			return (0);
	}
	return (1);
}
int type_hdoc_apnd(t_token *token)
{
	if (token)
	{
		if (token->type == t_HEREDOC || token->type == t_APPEND)
			return (0);
	}
	return (1);
}

/* Check PIPE syntax */
int	pipe_syntax(t_parser *parser, char *cmd)
{
	t_parser *tmp;
	(void)parser;
	
	tmp = initialize_parser(cmd);
	while (tmp->current_token->type != t_EOF)
	{
		if (tmp->current_token->type == t_PIPE)
		{
			g_gob.nb_cmd++;
			if (tmp->previous_token == NULL)
			
				return (1);
			else if (tmp->previous_token->type == t_PIPE || type_is_rederec(tmp->previous_token) == 0)
				return (1);
		}
		tmp->previous_token = tmp->current_token;
		tmp->current_token = get_next_token(tmp->lexer);
		if (tmp->current_token->type == t_EOF && tmp->previous_token->type == t_PIPE)
			return (1);
	}
	return (0);
}

/* Check redirection syntax */
int	redirect_syntax(t_parser *parser, char *cmd)
{
	t_parser *tmp;
	(void)parser;
	
	tmp = initialize_parser(cmd);
	while (tmp->current_token->type != t_EOF)
	{
		if (tmp->current_token->type == t_GREAT_THAN || tmp->current_token->type == t_LESS_THAN)
		{
			if (tmp->previous_token && (tmp->previous_token->type == t_GREAT_THAN || tmp->previous_token->type == t_LESS_THAN))
				return (1);
		}
		else if (tmp->current_token->type == t_HEREDOC || tmp->current_token->type == t_APPEND)
		{
			if (!tmp->previous_token || tmp->previous_token->type == t_GREAT_THAN || tmp->previous_token->type == t_LESS_THAN )
				return (1);
		}
		tmp->previous_token = tmp->current_token;
		tmp->current_token = get_next_token(tmp->lexer);
		if (tmp->current_token->type == t_EOF && type_is_rederec(tmp->previous_token) == 0)
				return (1);	
	}
	return (0);
}


int iterate_over_tokens_check_syntaxe(t_parser *parser, char *cmd)
{
	
	if ((pipe_syntax(parser, cmd) == 1) || (redirect_syntax(parser, cmd) == 1))
		return (err_msg("Bash : syntax error"));
	return (0);
}