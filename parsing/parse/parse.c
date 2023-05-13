/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/13 22:17:01 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_cmd	*start_parsing(t_parser *parser, char *cmd)
{
	//g_gob.ex_status = syntaxe_check(parser);
	g_gob.ex_status = iterate_over_tokens_check_syntaxe(parser, cmd);
	if (g_gob.ex_status != 258)
	{
		
	}
	// if suyntaxe error return NULL and free all the memory 
	return (NULL);
}



