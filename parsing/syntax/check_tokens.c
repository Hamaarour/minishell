/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:29:31 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/09 12:39:36 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"


int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	check_token_space(int j, char *str, char token)
{
	while (is_space(str[j]))
		j++;
	if (str[j] == token)
	{
		//printf("bash: syntax error near unexpected token `%c'\n", token);
		return (1);
	}
	return (0);
}

int	check_i_o_redirection(char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '<' && str[i + 1] == '>' )
			|| (str[i] == '>' && str[i + 1] == '<'))
		{
			//printf("bash: syntax error near unexpected token `%c'\n",
				//str[i + 1]);
			return (1);
		}
		else if (str[i] == '<')
		{
			j = i + 1;
			check_token_space(j, str, '>');
		}
		else if (str[i] == '>')
		{
			j = i + 1;
			check_token_space(j, str, '<');
		}
	}
	return (0);
}

int	check_here_doc(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (str[len - 1] == '>' || str[len - 1] == '<')
			{
				//printf("Error: Syntax error\n");
				return (1);
			}
			i += 2;
			while (is_space(str[i]))
				i++;
			if (str[i] == '<' || str[i] == '>')
			{
				//printf("Error: Syntax error\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_append(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			if (str[len - 1] == '>' || str[len - 1] == '<')
			{
				//printf("Error: Syntax error\n");
				return (1);
			}
			i += 2;
			while (is_space(str[i]))
				i++;
			if (str[i] == '<' || str[i] == '>')
			{
				//printf("Error: Syntax error\n");
				return (1);
			}
		}
	}
	return (0);
}

int	check_syntaxe(char *str)
{
	if (check_i_o_redirection(str) || check_here_doc(str) || check_append(str))
	{
		ft_putendl_fd("Syntaxe Error", 2);
		return (1);
	}
	return (0);
}
