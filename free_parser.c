/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:39:20 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/29 08:48:58 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parser(t_parser *parser)
{
	free(parser->current_token->val);
	free(parser->current_token);
	free(parser->previous_token->val);
	free(parser->previous_token);
	free(parser->lexer);
	free(parser);
}