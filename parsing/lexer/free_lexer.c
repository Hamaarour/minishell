/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:14:06 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/11 17:35:09 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/* free Tocken */
void	free_tocken(t_token *token)
{
	if (token)
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
