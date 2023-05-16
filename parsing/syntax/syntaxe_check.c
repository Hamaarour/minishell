/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/15 20:57:35 by hamaarou         ###   ########.fr       */
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

void free_env(t_env *env)
{
    if (env)
    {
        if (env->key)
            free(env->key);
        if (env->value)
            free(env->value);
        
        free_env(env->next); // Recursively free the next element in the linked list
        
        free(env); // Free the current t_env structure
    }
}
void free_token(t_token *token)
{
    if (token)
    {
        if (token->val)
            free(token->val);
        free(token);
    }
}

void free_lexer(t_lexer *lexer)
{
    if (lexer)
    {
        if (lexer->src)
            free(lexer->src);
        free_env(lexer->env);
        free(lexer);
    }
}
void free_parser(t_parser *parser)
{
    if (parser == NULL)
        return;

    free_lexer(parser->lexer);             // Assuming you have a function to free the lexer
    free_token(parser->current_token);      // Assuming you have a function to free a single token
    free_token(parser->previous_token);     // Assuming you have a function to free a single token

    free(parser);  // Free the t_parser structure itself
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
			{
				return (1);
			}
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
	{
		return (err_msg("Bash : syntax error"));
	}
	return (0);
}