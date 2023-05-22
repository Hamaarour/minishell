/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:39:27 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/22 02:34:54 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int num)
{
	if ((num >= 97 && num <= 122) || (num >= 65 && num <= 90)
		|| (num >= 48 && num <= 57) || num == '_')
		return (1);
	return (0);
}

int	ft_isalnum_original(int num)
{
	if ((num >= 97 && num <= 122) || (num >= 65 && num <= 90)
		|| (num >= 48 && num <= 57))
		return (1);
	return (0);
}
