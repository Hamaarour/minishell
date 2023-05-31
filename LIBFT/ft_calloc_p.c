/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:13:02 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/31 16:40:23 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_p(size_t count, size_t size)
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
