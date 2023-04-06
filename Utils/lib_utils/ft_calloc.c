/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:13:02 by hamaarou          #+#    #+#             */
/*   Updated: 2022/10/27 21:00:06 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;

	i = 0;
	if (count != 0 && size > SIZE_MAX / count)
		return (0);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	while (i < count * size)
		((char *)p)[i++] = 0;
	return ((void *)p);
}
