/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:24:58 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/03 16:40:17 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	open_file(char *file_name, int *fd)
{
	*fd = open(file_name, O_RDWR | O_CREAT, 0644);
	err_heredoc(*fd, file_name);
}

void	read_lines(char *delim, int fd)
{
	char	*line;
	char	*tmp;

	line = get_next_line(0);
	while (line != NULL && line[0] != '\0')
	{
		line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
			break ;
		else
		{
			if (find(line, '$') != -1)
			{
				tmp = line;
				line = expand(line);
				free(tmp);
			}
			ft_putendl_fd(line, fd);
		}
		free(line);
		line = get_next_line(0);
	}
}

void	close_file(int fd, char *line, char *file_name)
{
	if (line == NULL || line[0] == '\0')
		exit(0);
	free(line);
	free(file_name);
	close(fd);
}

void	h_d(char *delim, char *file_name)
{
	int		fd;
	char	*line;

	line = NULL;
	open_file(file_name, &fd);
	read_lines(delim, fd);
	close_file(fd, line, file_name);
}
