/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:15:00 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/11 16:52:23 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	int	*pcalloc;

	if (size != 0 && n > (SIZE_MAX / size))
		return (NULL);
	pcalloc = (int *)malloc(n * size);
	if (!pcalloc)
		return (NULL);
	ft_bzero(pcalloc, size * n);
	return (pcalloc);
}
