/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:46:59 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/21 17:48:27 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	type_is_char(t_token *token)
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
			|| token->type == t_HEREDOC || token->type == t_APPEND)
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

int	type_out_in(t_token *token)
{
	if (token)
	{
		if (token->type == t_LESS_THAN || token->type == t_GREAT_THAN)
			return (0);
	}
	return (1);
}

int	type_hd_apd(t_token *token)
{
	if (token)
	{
		if (token->type == t_HEREDOC || token->type == t_APPEND)
			return (0);
	}
	return (1);
}