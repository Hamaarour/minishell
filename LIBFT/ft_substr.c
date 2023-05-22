/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:22:13 by zjaddad           #+#    #+#             */
/*   Updated: 2022/10/26 22:30:48 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*test(unsigned int res, unsigned int len)
{
	char	*p;

	if (len > res)
		p = malloc(res + 1);
	else
		p = malloc(len + 1);
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*p;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	p = test(ft_strlen(s) - start, len);
	if (!p)
		return (NULL);
	while (s[i])
	{
		if (i == start)
		{
			while (s[i] && j < len)
				p[j++] = s[i++];
			break ;
		}
		i++;
	}
	p[j] = '\0';
	return (p);
}
