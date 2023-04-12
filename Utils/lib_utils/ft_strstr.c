/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:42:48 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/12 01:46:59 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	char	*haystack_new;

	haystack_new = (char *)haystack;
	i = 0;
	if (!needle[0])
		return (haystack_new);
	while (haystack_new[i])
	{
		j = 0;
		if (haystack_new[i] == needle[j])
		{
			while (haystack_new[i + j] && needle[j] && needle[j] == haystack_new[i + j])
				j++;
			if (!needle[j])
				return (&haystack_new[i]);
		}
		i++;
	}
	return (NULL);
}
