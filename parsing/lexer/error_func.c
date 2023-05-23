/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:44:40 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/23 12:12:46 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	error_func(int err)
{
	char	*str;

	str = strerror(err);
	//ft_putendl_fd(str, 2);
	//exit(EXIT_FAILURE);
}
