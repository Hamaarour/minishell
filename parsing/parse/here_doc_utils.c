/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:05:49 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/03 16:01:25 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../LIBFT/libft.h"

char	*generate_filename(void)
{
	char	*filename;
	int		fd;
	int		i;
	int		bytesread;

	filename = malloc(4 * sizeof(char) + 1);
	fd = open("/dev/random", O_RDONLY, 644);
	i = 0;
	bytesread = read(fd, filename, 1);
	while (i < 4 && bytesread != -1)
	{
		if (ft_isalpha(filename[i]))
		{
			bytesread = read(fd, filename + i + 1, 1);
			i++;
		}
		else
			bytesread = read(fd, filename + i, 1);
	}
	close(fd);
	filename[4] = '\0';
	return (filename);
}

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
