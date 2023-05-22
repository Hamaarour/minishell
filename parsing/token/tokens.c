/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:39:11 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/22 02:05:37 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/*
	function to initialize the tokens and return a pointer to the token
*/
t_token	*init_tokens(t_tokens_type typ, char *val)
{
	t_token	*token;

	token = (t_token *)ft_calloc_p(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = typ;
	token->val = val;
	return (token);
}
