/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_extra_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:41:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/22 02:07:34 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

/*
	The function works by iterating through the input string s one character
	at a time. If the current character is a space, it sets a flag to indicate
	that there are multiple spaces in a row. If the current character is not a
	space, it checks the flag to see if it needs to add a space to the output
	string before adding the current character. This way, the function only adds
	a single space between words, no matter how many spaces were originally
	in the input string.

*/
char	*remove_multiple_spaces(char* s)
{
	int		space;
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	space = 0;
	new = malloc(ft_strlen(s) + 1);
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
	return (new);
}
