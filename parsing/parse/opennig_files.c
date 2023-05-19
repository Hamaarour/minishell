/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opennig_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:56:09 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/19 18:38:05 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	out_file(char *file_name, t_data_cmd **tmp)
{
	tmp->fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp->fd_out == -1)
	{
		ft_putstr_fd("Error: No such file or directory", 2);
	
	}
}


void 	in_file(char *file_name, t_data_cmd *tmp)
{
	tmp->fd_in = open(file_name, O_RDONLY, 0644);
	if (tmp->fd_in == -1)
	{
		ft_putstr_fd("Error: No such file or directory", 2);
	}
}

void	append_file(char *file_name, t_data_cmd *tmp)
{
	tmp->fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tmp->fd_out == -1)
	{
		ft_putstr_fd("Error: No such file or directory", 2);
	}
}
