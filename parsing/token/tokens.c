/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:39:11 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/01 14:24:57 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
	function to initialize the tokens and return a pointer to the token
*/
t_token	*init_tokens(t_tokens_type typ, char *val)
{
	t_token	*token;

	token = (t_token *)ft_calloc(0,sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = typ;
	token->val = val;
	return (token);
}
