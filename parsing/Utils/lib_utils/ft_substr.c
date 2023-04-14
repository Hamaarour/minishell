/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:17:17 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/14 16:00:26 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*b;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	b = malloc((len + 1));
	if (!b)
		return (NULL);
	while (s[start] != '\0' && i < len && start < ft_strlen(s))
	{
		b[i] = s[start];
		start++;
		i++;
	}
	b[i] = 0;
	return (b);
}
