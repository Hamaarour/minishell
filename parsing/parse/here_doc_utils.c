/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:05:49 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/04 11:50:00 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../LIBFT/libft.h"

char	*dollar(char *s, int *i)
{
	char	*tmp;
	char	*str;
	int		j;
	char	*tmp2;

	j = *i;
	(*i)++;
	if (s[*i] == '?')
	{
		str = ft_itoa(g_glob.ex_status);
		return (str);
		(*i)++;
	}
	while (s[*i] && (ft_isalnum(s[*i])))
		(*i)++;
	tmp = ft_substr(s, j + 1, *i - j - 1);
	tmp2 = get_envairment_var(tmp);
	free(tmp);
	(*i)--;
	return (tmp2);
}

char	*expand(char *line)
{
	char	*str;
	int		i;
	char	*tmp;
	char	*r;

	i = 0;
	str = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && g_glob.to_expand != 1)
			tmp = dollar(line, &i);
		else
		{
			r = ft_substr(line, i, 1);
			str = ft_strjoin(str, r);
			free(r);
			i++;
			continue ;
		}
		str = ft_strjoin(str, tmp);
		free(tmp);
		i++;
	}
	return (str);
}

int	find(char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

void	handle_error_and_return(char *file_name)
{
	unlink(file_name);
	free(file_name);
}
