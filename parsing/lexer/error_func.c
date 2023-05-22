/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:44:40 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/22 02:07:08 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	error_func(int err)
{
	char	*str;

	str = strerror(err);
	//ft_putendl_fd(str, 2);
	//exit(EXIT_FAILURE);
}
