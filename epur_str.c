/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:28:27 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/05 23:06:34 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*epur_str(char* s)
{
	int		space;
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	space = 0;
	while (*s == ' ' || *s == '\t')
		s++;
	new = malloc(strlen(s) + 1);
	if (!new)
		return NULL;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			space = 1;
		else
		{
			if (space)
			{
				new[j++] = ' ';
				space = 0;
			}
			new[j++] = s[i];
		}
		i++;
	}
	new[j] = '\0';
	return new;
}
