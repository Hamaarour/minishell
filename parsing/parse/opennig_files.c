/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opennig_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:56:09 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/29 21:15:25 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

int	out_file(char *file_name, int *fd_out)
{
	if (*fd_out > 2)
		close(*fd_out);
	*fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		ft_putendl_fd("Bash Error: No such file or directory", 2);
		glob.ex_status = 1;
		return (1);
	}
	return (0);
}

int	in_file(char *file_name, int *fd_in)
{
	if (*fd_in > 2)
		close(*fd_in);
	*fd_in = open(file_name, O_RDONLY, 0644);
	if (*fd_in == -1)
	{
		ft_putendl_fd("Bash Error: No such file or directory", 2);
		glob.ex_status = 1;
		return (1);
	}
	return (0);
}

int	append_file(char *file_name, int *fd_out)
{
	if (*fd_out > 2)
		close(*fd_out);
	*fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_out == -1)
	{
		ft_putendl_fd("Bash Error: No such file or directory", 2);
		glob.ex_status = 1;
		return (1);
	}
	return (0);
}


int	heredoc_file(char *delim, int *fd_in)
{
	char	*file_name;
	char *line;

	file_name = generate_filename();
	if (*fd_in > 2)
		close(*fd_in);
	int pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		*fd_in = open(file_name, O_WRONLY | O_CREAT, 0644);
		if (*fd_in == -1)
		{
			ft_putendl_fd("Bash Error: No such file or directory", 2);
			glob.ex_status = 1;
			return (free(file_name), 1);
		}
		line = get_next_line(0);
		char **arr = ft_split_p(line, '\n');
		while (line != NULL && ft_strcmp(arr[0], delim) != 0)
		{
			ft_putendl_fd(line, *fd_in);
			free(line);
			line = get_next_line(0);
		}
	}
	free(file_name);
	return (0);
}