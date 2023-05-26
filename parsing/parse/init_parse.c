/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:23:02 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/26 22:44:02 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/*
    function to initialize the parser and return a pointer to the parser struct 
*/
t_parser	*initialize_parser(char *input)
{
	t_parser	*parser;
	t_lexer		*lexer;

	parser = (t_parser *)ft_calloc_p(1, sizeof(t_parser));
	if (!parser)
		return (NULL);
	lexer = init_lexer(input);
	parser->lexer = lexer;
	parser->current_token = get_next_token(lexer);
	if (parser->current_token == NULL)
	{
		return (NULL);
	}
	parser->previous_token = NULL;
	return (parser);
}
