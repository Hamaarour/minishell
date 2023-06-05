/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/05 14:10:19 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	free_arg_cmd(t_args *arg)
{
	t_args	*tmp;

	while (arg)
	{
		tmp = arg;
		arg = arg->next;
		free(tmp->args);
		free(tmp);
	}
}

t_args	*create_node(t_parser *parser, int *fd_in, int *fd_out)
{
	t_args	*arg;
	int		flag;

	flag = 0;
	arg = NULL;
	while (parser->current_token->type != t_PIPE
		&& parser->current_token->type != t_EOF)
	{
		if (is_redirection_token(parser))
		{
			if (handle_redirection(parser, fd_in, fd_out, &flag) == 1)
				return (free_arg_cmd(arg), NULL);
		}
		else if (!is_redirection(parser->current_token->type))
			ft_add_back_arg(&arg, ft_new_arg(parser->current_token->val));
		free_prev(parser);
		parser->previous_token = parser->current_token;
		update_current_token(parser);
		if (parser->current_token == NULL)
			return (free(parser->current_token), NULL);
	}
	return (arg);
}

int	divid_cmd(t_parser *parser, t_data_cmd **cmd_data)
{
	t_args	*arg;
	int		in;
	int		out;

	arg = NULL;
	in_out(&in, &out);
	while (parser->current_token != NULL && parser->current_token->type != 6)
	{
		if (parser->current_token->type != t_PIPE)
		{
			arg = create_node(parser, &in, &out);
			if (arg != NULL)
				ft_add_back_cmd(cmd_data, ft_new_cmd(arg, in, out));
			else
				return (0);
			in_out(&in, &out);
		}
		if (parser->current_token != NULL)
			free(parser->current_token->val);
		free(parser->current_token);
		parser->current_token = get_next_token(parser->lexer, 0);
		if (parser->current_token == NULL)
			return (reinitialize_parser(parser), 1);
	}
	return (0);
}

int	start_parsing(t_parser *parser, t_data_cmd **cmd_data)
{
	int	i;

	i = iterate_over_tokens_check_syntaxe(parser);
	if (i == 1)
		return (1);
	else
	{
		if (i == 42)
		{
			if (divid_cmd(parser, cmd_data) == 1)
			{
				cleanup_parser(parser);
				return (1);
			}
			return (0);
		}
	}
	return (1);
}
