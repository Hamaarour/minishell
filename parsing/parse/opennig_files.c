/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opennig_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:56:09 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/04 11:56:52 by hamaarou         ###   ########.fr       */
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
		g_glob.nb_err++;
		g_glob.ex_status = 1;
		*fd_out = -5;
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
		g_glob.nb_err++;
		g_glob.ex_status = 1;
		*fd_in = -5;
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
		g_glob.nb_err++;
		g_glob.ex_status = 1;
		*fd_out = -5;
		return (1);
	}
	return (0);
}

int	child_process_heredoc(char *delim, char *file_name)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
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
	return (0);
}

int	heredoc_file(char *delim, int *fd_in)
{
	char	*file_name;
	char	*s;
	char	*tmp;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (*fd_in > 2)
		close(*fd_in);
	file_name = generate_filename();
	tmp = ft_strdup("/tmp/");
	s = file_name;
	file_name = ft_strjoin(tmp, file_name);
	free(s);
	if (child_process_heredoc(delim, file_name) == 1)
		return (1);
	*fd_in = open(file_name, O_RDONLY, 0644);
	if (*fd_in == -1)
	{
		g_glob.nb_err++;
		g_glob.ex_status = 1;
		*fd_in = -5;
		return (1);
	}
	return (handle_error_and_return(file_name), 0);
}

/*void	handle_open_error_and_return(int *fd_in)
{
	g_glob.nb_err++;
	g_glob.ex_status = 1;
	*fd_in = -5;
}

int	heredoc_file(char *delim, int *fd_in)
{
	char	*file_name;
	int		pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (*fd_in > 2)
		close(*fd_in);
	file_name = generate_filename();
	pid = fork();
	if (pid == -1)
		return (free(file_name), 1);
	if (pid == 0)
	{
		signal(SIGINT, ctrl_handler);
		h_d(delim, file_name);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		return (handle_error_and_return(file_name), 1);
	*fd_in = open(file_name, O_RDONLY, 0644);
	if (*fd_in == -1)
		return (handle_open_error_and_return(fd_in), 1);
	unlink(file_name);
	return (free(file_name), 0);
}
*/
