/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CD_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:04:26 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/27 12:07:15 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	to_home(char *home, t_env *evr)
{
	update_pwd(home, evr);
	free(home);
}
