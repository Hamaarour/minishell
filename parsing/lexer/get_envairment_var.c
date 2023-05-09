/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envairment_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:37:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/09 20:58:03 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char    *get_envairment_var(char *to_find, t_lexer *lexer)
{
	t_env	*env_tmp;
	char	*var;
	int		i;
	
	i = 0;
	env_tmp = lexer->env;
	var = NULL;
	while(env_tmp->next)
	{
		if (ft_strcmp(env_tmp->key, to_find) == 0)
		{
			var = ft_strdup(env_tmp->value);
			if (var == NULL)
				error_func(errno);
		}
		env_tmp = env_tmp->next;	
	}
	return (var);
}
