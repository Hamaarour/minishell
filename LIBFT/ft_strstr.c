/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:42:48 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/22 02:35:44 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t j;

	if (!haystack || !needle) // Check for NULL pointers
		return NULL;

	if (!*needle) // Check for empty needle string
		return (char *)haystack; // Cast to char* to avoid const return warning

	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j]) // Use nested while loop for comparison
			j++;
		if (!needle[j]) // Check if entire needle string is found
			return (char *)&haystack[i]; // Cast to char* to avoid const return warning
		i++;
	}
	return NULL;
}
