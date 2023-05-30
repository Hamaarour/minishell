/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envairment_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:37:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/30 17:48:22 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

char    *get_envairment_var(char *to_find)
{
	char	*var = NULL;
	t_env  *env_p = glob.env_p;

	while(env_p->next)
	{
		if (ft_strcmp(env_p->key, to_find) == 0)
		{
			var = ft_strdup(env_p->value);
			if (var == NULL)
				error_func(errno);
		}
		env_p = env_p->next;	
	}
	return (var);
}