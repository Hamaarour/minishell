/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:44:42 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/12 01:15:46 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	t_ati	var;

	var.i = 0;
	var.result = 0;
	var.sign = 1;
	while ((s[var.i] == ' ' || (s[var.i] >= 9 && s[var.i] <= 13)))
		var.i++;
	if ((s[var.i] == '+' || s[var.i] == '-') && s[var.i + 1] != '\0')
	{
		if (s[var.i] == '-')
			var.sign = -1;
		var.i++;
	}
	while (s[var.i])
	{
		if (s[var.i] < '0' || s[var.i] > '9')
			return (0);
		var.result = var.result * 10 + (s[var.i] - 48);
		var.i++;
	}
	if (var.result > __LONG_LONG_MAX__ && var.sign == 1)
		return (0);
	if (var.result > (unsigned long long)__LONG_LONG_MAX__ + 1 && var.sign == -1)
		return (0);
	return (var.result * var.sign);
}
