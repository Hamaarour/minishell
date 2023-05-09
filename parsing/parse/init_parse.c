/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:23:02 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/08 18:32:54 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
    function to initialize the parser and return a pointer to the parser struct 
*/
t_parser	*init_parser(t_lexer *lexer)
{
    t_parser	*parser;

    parser = (t_parser *)ft_calloc(1, sizeof( t_parser));
    if (!parser)
        return (NULL);
    parser->lexer = lexer;
    parser->current_token = get_next_token(lexer);
    return (parser);
}
