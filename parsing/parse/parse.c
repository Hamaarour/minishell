/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/10 19:29:58 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_cmd    *start_parsing(t_parser *parser)
{
    if (parser->current_token->type != t_EOF)
    {
        if (syntaxe_check(parser) == 0)
            return (NULL);
        
    }
    return (NULL);
}



