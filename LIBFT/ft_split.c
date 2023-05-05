/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:15:26 by zjaddad           #+#    #+#             */
/*   Updated: 2022/10/27 22:01:45 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	substr_count(char const *s, char c)
{
	int	hndl_i;
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (s[index])
	{
		while (s[index] == c)
			index++;
		hndl_i = index;
		while (s[index] && s[index] != c)
			index++;
		if (hndl_i < index)
			count++;
	}
	return (count);
}

static int	substr_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*fail_allocate(char **as, int j)
{
	if (as[j] == NULL)
	{
		while (j >= 0)
			free(as[--j]);
		free(as);
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**as;

	if (!s)
		return (NULL);
	substr_count(s, c);
	as = (char **)malloc(sizeof(as) * (substr_count(s, c) + 1));
	if (!as)
		return (NULL);
	i = 0;
	j = 0;
	while (j < substr_count(s, c))
	{
		while (s[i] == c)
			i++;
		len = substr_len(s + i, c);
		as[j] = ft_substr(s, i, len);
		fail_allocate(as, j);
		j++;
		i += len;
	}
	as[j] = NULL;
	return (as);
}
