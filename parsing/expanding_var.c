/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:29:00 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/12 01:49:07 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	This function replace_var takes in three parameters: splited_Str, var, and to_find_str.
	It iterates through each string in splited_Str using a while loop, checks if to_find_str
	is a substring using strstr, finds the position of '$' using strstr, replaces '$' with a
	null terminator, concatenates var with the truncated string using ft_strjoin, frees the
	original memory, and assigns the new string to splited_Str. Finally, it returns the
	modified splited_Str.
*/
char	**replace_var(char **splited_Str, char *var, char *to_find_str)
{
	t_replace_var	rv;

	rv.i = 0;
	while (splited_Str[rv.i])
	{
		if (ft_strstr(splited_Str[rv.i], to_find_str) != NULL)
		{
			rv.tmp = ft_strstr(splited_Str[rv.i], "$");
			if (rv.tmp != NULL)
			{
				rv.index = rv.tmp - splited_Str[rv.i];
				rv.start = rv.index + ft_strlen(to_find_str);
				rv.truncated_str = ft_substr(splited_Str[rv.i], 0, rv.index);
				rv.last_str = ft_substr(splited_Str[rv.i], rv.start + 1, ft_strlen(splited_Str[rv.i]) - rv.start);
				rv.new_str = ft_strjoin(rv.truncated_str, var);
				free(splited_Str[rv.i]);
				splited_Str[rv.i] = ft_strjoin(rv.new_str, rv.last_str);
				free(rv.truncated_str);
			}
		}
		rv.i++;
	}
	return (splited_Str);
}

/*
	Inside the loop, the function checks if the current element in the "splited_str"
	array contains a '$' sign by calling the "check_dollar" function, passing the current
	element and the '$' character as arguments. If the "check_dollar" function returns 1,
	it means a '$' sign was found, and the function proceeds to extract the corresponding
	environment variable.

	The function uses another loop to find the position of the character immediately following
	the '$' sign, which is the starting position for the environment variable name. The loop
	increments the "j" variable until it reaches the '$' sign.

	After finding the starting position for the environment variable name, the function checks
	if the character immediately following the '$' sign is an alphanumeric character using the
	ft_isalnum() function. If it is not, the loop is skipped to the next iteration using continue,
	effectively ignoring the input and moving on to the next element in the array.
*/

void	expand_var(t_str *str, t_env *env_p)
{
	int		i;
	int		j;
	int		start;
	char	*tmp_var;
	char	*s;

	i = 0;
	while (str->splited_str[i])
	{
		j = 0;
		if (check_dollar(str->splited_str[i], '$') == 1)
		{
			while (str->splited_str[i][j] != '$')
				j++;
			start = j + 1;
			if (!ft_isalnum(str->splited_str[i][start]))
			{
				i++;
				continue ;
			}
			j = start;
			while (str->splited_str[i][j] != '\0' && ft_isalnum(str->splited_str[i][j]))
				j++;
			tmp_var = ft_substr(str->splited_str[i], start, j - start);
			s = find_var(env_p, tmp_var);
		}
		i++;
	}
	str->splited_str = replace_var(str->splited_str, s, tmp_var);
}
