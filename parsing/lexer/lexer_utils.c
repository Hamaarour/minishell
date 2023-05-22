/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:50:54 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/22 02:07:26 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/*
	outfile 
	append
*/
t_token	*rederection_great(t_lexer *lexer)
{
	advance_lexer(lexer);
	if (lexer->c == '>')
		return (advance_to_next_tocken(lexer, init_tokens(t_APPEND,
					ft_strdup(">>"))));
	return (init_tokens(t_GREAT_THAN, ft_strdup(">")));
}

/*
infile
here document
*/
t_token	*rederection_less(t_lexer *lexer)
{
	advance_lexer(lexer);
	if (lexer->c == '<')
		return (advance_to_next_tocken(lexer, init_tokens(t_HEREDOC,
					ft_strdup("<<"))));
	return (init_tokens(t_LESS_THAN, ft_strdup("<")));
}