/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opennig_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:56:09 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/01 19:41:48 by hamaarou         ###   ########.fr       */
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
		g_glob.ex_status = 1;
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
		g_glob.ex_status = 1;
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
		g_glob.ex_status = 1;
		return (1);
	}
	return (0);
}

void	h_d(char *delim, char *file_name)
{
	int		fd;
	char	*line;
	char	*tmp;

	line = NULL;
	
	fd = open(file_name, O_RDWR | O_CREAT, 0644);
	err_heredoc(fd, file_name);
	line = get_next_line(0);
	if (line ==NULL)
		printf("her\n");
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
	if (line == NULL || line[0] == '\0')
	{
		printf("her\n");
		ctrl_d_handler();
	}
	free(line);
	close(fd);
}

int	heredoc_file(char *delim, int *fd_in)
{
	char	*file_name;
	int		pid;
	int		status;
	char *s;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (*fd_in > 2)
		close(*fd_in);
	file_name = generate_filename();
	char *tmp = ft_strdup("/tmp/");
	s = file_name;
	file_name = ft_strjoin(tmp, file_name);
	free(s);
	if ((pid = fork()) == -1)
		return (free(file_name), 1);
	
	if (pid == 0)
	{
		signal(SIGINT, ctrl_handler);
		h_d(delim, file_name);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		return (unlink(file_name), 1);
	*fd_in = open(file_name, O_RDONLY, 0644);
	if (*fd_in == -1)
	{
		ft_putendl_fd("Bash Error: No such file or directory aaaa", 2);
		g_glob.ex_status = 1;
		return (1);
	}
	unlink(file_name);
	free(file_name);
	return (0);
}
