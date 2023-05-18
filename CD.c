/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CD.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:25:04 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/17 00:59:14 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../libft/libft.h"
#include "minishell.h"

int ft_lstsizes(t_args *lst)
{
	t_args	*lent;
	int		i;

	i = 0;
	if (lst)
	{
		lent = lst;
		while (lent)
		{
			lent = lent->next;
			i++;
		}
	}
	return (i);
}

void	update_old(char *old_p, t_env *evr)
{
	t_env *tmp;

	tmp = evr;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(old_p);
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(char *pwd, t_env *evr)
{
	t_env *tmp;

	tmp = evr;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(pwd);
			break ;
		}
		tmp = tmp->next;
	}
}

void	get_home(t_env *evr)
{
	t_env	*tmp;
	char	*old_p;
	char	*home;

	home = NULL;
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
				home = getcwd(NULL, 0);
			break ;
		}
		tmp = tmp->next;
	}
	update_pwd(home, evr);
	free(old_p);
	if (home)
		free(home);
}

void cd(t_args *cmd)
{
    int args;
    char *pwd;
    char *old_p;

    glob.ex_status = 0;
    args = ft_lstsizes(cmd);
    if (args == 1)
        get_home(glob.env_p);
    else
    {
        old_p = getcwd(NULL, 0);
        update_old(old_p, glob.env_p);
        if (chdir(cmd->next->args) == -1)
        {
            printf("No such file or directory\n");
            glob.ex_status = 1;
        }
        pwd = getcwd(NULL, 0);
        update_pwd(pwd, glob.env_p);
		free(old_p);
		free(pwd);
    }
}
