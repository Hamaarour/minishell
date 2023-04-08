/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:27:57 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/07 22:57:01 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int j)
{
	int		i;
	char	c;
	int		len;

	i = 0;
	c = (char)j;
	len = ft_strlen(str);
	if (c == '\0')
		return (&str[len]);
	while (i < len)
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (0);
}
