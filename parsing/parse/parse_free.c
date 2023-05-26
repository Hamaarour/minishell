/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:51:19 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/26 12:27:41 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/* free Tocken */
void	free_tok(t_token *token)
{
	if (token != NULL)
	{
		if (token->type != t_CHAR)
		{
			if (token->val)
				free(token->val);
		}
		if (token)
			free(token);
	}
}

/* free a parser */

void	free_parsing(t_parser *parser)
{
	if (parser != NULL)
	{
		if (parser->lexer != NULL)
		{
			free(parser->lexer->src);
			free(parser->lexer);
		}
		if (parser->previous_token)
			free_tok(parser->previous_token);
		if (parser->current_token)
			free_tok(parser->current_token);
		if (parser)
			free(parser);
	}
}

//free args
void	free_args_list(t_args *head)
{
	t_args	*current;
	t_args	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		// Free the args field if applicable
		if (current->args != NULL)
			free(current->args);
		free(current);
		current = next;
	}
}

// free cmd
void	free_all(t_data_cmd *cmd_data)
{
	while (cmd_data)
	{
		free_args_list(cmd_data->args);
		cmd_data->fd_in = 0;
		cmd_data->fd_out = 0;
		free(cmd_data);
		cmd_data = cmd_data->next;
	}
}