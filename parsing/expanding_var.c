/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:29:00 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/09 23:36:33 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
				return 1;
			j = 0;
		}
		i++;
	}
	return 0;
}

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
	int		i;
	int		index;
	char	*truncated_str;
	char	*tmp;

	i = 0;
	while (splited_Str[i])
	{
		if (strstr(splited_Str[i], to_find_str) != NULL)
		{
			char *tmp = strstr(splited_Str[i], "$");
			if (tmp != NULL)
			{
				index = tmp - splited_Str[i];
				truncated_str = ft_substr(splited_Str[i], 0, index);
				free(splited_Str[i]);
				splited_Str[i] = new_str;
				free(truncated_str);
			}
		}
		i++;
	}
	return splited_Str;
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
