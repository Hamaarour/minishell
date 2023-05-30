/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opennig_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:56:09 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/31 00:36:06 by hamaarou         ###   ########.fr       */
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

char	*dollar(char *s, int *i)
{
	char	*tmp;
	char	*str;
	int		j;

	j = *i;
	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
	}
	while (s[*i] && (ft_isalnum(s[*i])))
		(*i)++;
	tmp = ft_substr(s, j + 1, *i - j - 1);
	char *tmp2 = get_envairment_var(tmp);
	free(tmp);
	(*i)--;
	return (tmp2);
}
//"hello $USER ASDASD"
char	*expand(char *line)
{
	char	*str;
	int		i;
	char *tmp;

	i = 0;
	str = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
			tmp = dollar(line, &i);
		else
		{
			char *r = ft_substr(line, i, 1);
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

int	heredoc_file(char *delim, int *fd_in)
{
	char	*file_name;
	char *line;
	int fd;
	
	file_name = generate_filename();

	fd = open(file_name, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putendl_fd("Bash Error: No such file or directory", 2);
		glob.ex_status = 1;
		return (free(file_name), 1);
	}
	line = get_next_line(0);
	while (line != NULL)
	{
		line[ft_strlen(line) - 1] = '\0';
		if (strncmp(line, delim, ft_strlen(delim)) == 0)
			break ;
		else
		{
			if (find(line, '$') != -1)
			{
				char *tmp = line;
				line = expand(line);
				free(tmp);
			}
			ft_putendl_fd(line, fd);
		}
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd);
	*fd_in = open(file_name, O_RDONLY, 0644);
	if (*fd_in == -1)
	{
		ft_putendl_fd("Bash Error: No such file or directory", 2);
		glob.ex_status = 1;
		return (1);
	}
	// if (*fd_in > 2)
	// 	close(*fd_in);
	free(file_name);
	return (0);
}



/*
char			*value;
	int		i;
	int				j;
	int		k;
	char			res[1024];

	i = 0;
	value = NULL;
	while (line[i] && line[i] != '$')
	{
		res[i] = line[i];
		i++;
	}
	if (line[i] == '$')
	{
		int start = i + 1;
		char *tmp;
		k = i;
		i++;
		while (line[i] && ft_isalnum(line[i]))
			i++;
		tmp = ft_substr(line,start,i);//USER\n
		printf("tmp 1= %s\n",tmp);
		while (tmp[i--] == ' ')
			res[k++] = ' ';
		tmp = ft_strtrim(tmp, "'\"\n ");//USER
		printf("tmp 2= %s\n",tmp);
		value = get_envairment_var(tmp);//hamaarou
		printf("value = %s\n",value);
		if (value)
		{
			j = 0;
			while (value[j])
				res[k++] = value[j++];
		}
	}
	while (line[++i])
		res[k++] = line[i];
	res[k] = '\0';
	return (ft_strdup(res));
*/