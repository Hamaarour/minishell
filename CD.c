/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CD.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:25:04 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/12 04:45:34 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../libft/libft.h"
#include "minishell.h"

void	update_old(char *old_p, t_env *evr)
{
	t_env *tmp;

	tmp = evr;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD"))
			tmp->value = old_p;
		tmp = tmp->next;
	}
}

void	update_pwd(char *pwd, t_env *evr)
{
	t_env *tmp;

	tmp = evr;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD"))
			tmp->value = pwd;
		tmp = tmp->next;
	}
}

void	get_home(t_env *evr)
{
	t_env	*tmp;
	char	*old_p;
	char	*home;

	tmp = evr;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
		{
			old_p = getcwd(NULL, 0);
			update_old(old_p, evr);
			if (chdir(tmp->value) == -1)
				printf("ERROR: chdir\n");
			else
			{
				home = getcwd(NULL, 0);
				printf("%s\n", home);
			}
		}
		tmp = tmp->next;
	}
	update_pwd(home, evr);
}

void	cd(char **cmd, t_env *envr)
{
	int	args;
	char	*pwd;
	char	*old_p;

	glob.ex_status = 0;
	args = args_len(cmd);
	if (args == 1)
		get_home(envr);
	else
	{
		old_p = getcwd(NULL, 0);
		update_old(old_p, envr);
		if (chdir(cmd[1]) == -1)
		{
			printf("No such file or directory\n");
			glob.ex_status = 1;
		}
		pwd = getcwd(NULL, 0);
		update_pwd(pwd, envr);
	}
}
