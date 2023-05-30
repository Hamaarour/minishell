/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:05:49 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/30 23:06:59 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../LIBFT/libft.h"

char	*generate_filename(void)
{
	char	*filename;
	int 	fd;
	int		i;
	size_t	bytesRead;

	filename = malloc(4 * sizeof(char) + 1);
	fd = open("/dev/random", O_RDONLY, 644);
	i = 0;
	bytesRead = read(fd, filename, 1);
	while (i < 4 && bytesRead != -1)
	{
		if (ft_isalpha(filename[i]))
		{
			bytesRead = read(fd, filename + i + 1, 1);
			i++;
		}
		else
			bytesRead = read(fd, filename + i, 1);
	}
	close(fd);
	filename[4] = '\0';
	return (filename);
}