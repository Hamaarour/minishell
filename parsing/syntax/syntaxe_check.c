/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/10 19:57:57 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"






int syntaxe_check(t_parser *parser)
{
    if (parser->current_token->type == t_PIPE)
    {
        if (parser->previous_token->type == t_CHAR)
        {
            printf("sadasd\n");
            return (0);
        }
        else
        {
            g_gob.ex_status = 258;
            ft_putendl_fd("bash : syntax error", 2);
            return (0);
        }
    }    
    return (1);
}


