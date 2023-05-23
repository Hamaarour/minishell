/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:30:22 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/23 16:57:18 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr_G(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup_G(const char *s1)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)malloc(ft_strlen_G((char *)s1) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr_G(char const *s, unsigned int start, size_t len)
{
	char	*b;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen_G(s))
		return (ft_strdup_G(""));
	if (len > ft_strlen_G(s))
		len = ft_strlen_G(s) - start;
	b = malloc((len + 1));
	if (!b)
		return (NULL);
	while (s[start] != '\0')
	{
		b[i] = s[start];
		start++;
		i++;
	}
	b[i] = 0;
	return (b);
}

char	*ft_strjoin_G(char **s, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!*s)
	{
		*s = (char *)malloc(1 * sizeof(char));
		(*s)[0] = '\0';
	}
	str = malloc(sizeof(char) * ((ft_strlen_G(*s) + ft_strlen_G(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while ((*s)[++i] != '\0')
		str[i] = (*s)[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen_G(*s) + ft_strlen_G(buff)] = '\0';
	free(*s);
	*s = 0;
	return (str);
}

size_t	ft_strlen_G(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
