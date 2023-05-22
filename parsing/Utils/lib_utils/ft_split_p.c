/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:27:03 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/21 22:26:19 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static int	free_space(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	return (1);
}

static char	**aloc(char const *s, char sep)
{
	char	**k;

	(void)sep;
	(void)s;
	k = (char **)ft_calloc_p((1), sizeof(char *));
	if (!k)
		return (NULL);
	return (k);
}

static int	ww(char const *s, char sep, int i)
{
	(void)sep;
	while (s[i] && s[i] != sep)
		i++;
	return (i);
}

char	**ft_split_p(char const *s, char sep)
{
	char **p;
	size_t start;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	p = aloc(s, sep);
	if (!p)
		return (NULL);
	while (s[i])
	{
		if (s[i] != sep)
		{
			start = i;
			i = ww(s, sep, i);
			p[j++] = ft_substr_p(s, start, (i - start));
			(!p) && (free_space(p));
		}
		else
			i++;
	}
	return (p);
}