/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:29:00 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/08 03:56:58 by hamaarou         ###   ########.fr       */
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

 void	expand_var(t_str *str, t_env *env_p)
 {
	int		i;
	int		j;
	int		start;
	char	*tmp_var;
	(void)(env_p);
	i = 0;

	while (str->splited_str[i])
	{
		j = 0;
		if (check_dollar(str->splited_str[i], '$') == 1)
		{
			while (str->splited_str[i][j] != '$')
				j++;
			start = j + 1;
			if (str->splited_str[i][start] == ' ' )
				break ;
			while (str->splited_str[i][j] != '\0' || ft_isalnum(str->splited_str[i][j]))
				j++;
			tmp_var = ft_substr(str->splited_str[i], start, j);
			printf("tmp_var = %s    ", tmp_var);
		}
		i++;
	}
	printf("\n");
}
