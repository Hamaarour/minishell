/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:30:16 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/23 16:58:54 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ss(int fd, char *buffer, char *tmp, char **string)
{
	int	bytes;

	bytes = 1;
	while (ft_strchr_G(tmp) == 0 && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (bytes == -1)
			{
				free(*string);
				*string = NULL;
				free(tmp);
				tmp = NULL;
			}
			break ;
		}
		buffer[bytes] = '\0';
		tmp = ft_strjoin_G(&tmp, buffer);
	}
	return (tmp);
}

char	*ft_read_G(int fd, char **string)
{
	char	*buffer;
	char	*tmp;

	tmp = 0;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	tmp = ft_strjoin_G(string, buffer);
	tmp = ss(fd, buffer, tmp, string);
	free(buffer);
	if (tmp && tmp[0] == 0)
	{
		free(tmp);
		return (0);
	}
	return (tmp);
}

char	*get_line_ss(char **string, char *line)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	buff = malloc((i + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (++j < i)
		buff[j] = line[j];
	buff[j] = '\0';
	*string = ft_substr_G(line, i, ft_strlen_G(line));
	free(line);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*string;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_read_G(fd, &string);
	if (!line)
		return (NULL);
	line = get_line_ss(&string, line);
	return (line);
}
