/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/11 19:14:15 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_cmd	*start_parsing(t_parser *parser)
{
	g_gob.ex_status = syntaxe_check(parser);
	if (g_gob.ex_status != 258)
	{
		// syntaxe correct
		
	}
	// if suyntaxe error return NULL and free all the memory 
	return (NULL);
}



