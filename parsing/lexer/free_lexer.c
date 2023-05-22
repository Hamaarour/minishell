/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:14:06 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/22 03:07:43 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

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
