/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:30:38 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/10 22:30:38 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	this function check if a dollar ($) found in the
	string if found return true else return false
*/
int	ft_find(char *str, char c)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
check if a dollar ($) found in the string if found
return true(1) else return false(0)
*/
int	check_dollar(char *str, char dollar)
{
	if (ft_find(str, dollar) == 1)
		return (1);
	return (0);
}

/*
	this function find_var return the value of the envirment variable
	if the key is found in the envirment variables else return NULL
*/
char	*find_var(t_env *env_p, char *var)
{
	t_env	*tmp;

	tmp = env_p;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
	this function check if the string is a substring of another string
	if the string is a substring return true(1) else return false(0)
*/
int	is_substring(char *str, char *to_find)
{
	int	i;
	int	j ;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == to_find[0])
		{
			while (to_find[j] && (str[i + j] == to_find[j]))
				j++;
			if (to_find[j] == '\0')
				return (1);
			j = 0;
		}
		i++;
	}
	return (0);
}
