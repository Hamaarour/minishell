/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 03:21:45 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/16 06:13:57 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../libft/libft.h"
#include "minishell.h"

void	check_builtin(t_args *cmd, int fd, t_env *envr)
{
	if (!ft_strcmp(cmd->args, "echo"))
		echo(cmd, fd);
	else if (!ft_strcmp(cmd->args, "pwd"))
		pwd(cmd, fd);
	else if (!ft_strcmp(cmd->args, "cd"))
		cd(cmd);
	else if (!ft_strcmp(cmd->args, "unset"))
		unset(cmd);
	else if (!ft_strcmp(cmd->args, "env"))
		env(fd);
	else if (!ft_strcmp(cmd->args, "exit"))
		ft_exit(cmd);
	// else if (!ft_strcmp(cmd->args, "export"))
	// 	ft_export(cmd, fd);
	else
		printf("NO BUILTINS\n");
}

t_args *ft_lstlast_arg(t_args *lst)
{
	t_args	*last;

	last = NULL;
	
	if (lst)
	{
		last = lst;
		while (last->next)
			last = last->next;
	}
	return (last);
}

t_args *ft_lstnew_arg(void *content)
{
	t_args	*p = NULL;
	
	p = malloc(sizeof(t_args));
	if (p == NULL)
		return (NULL);
	p->args = content;
	p->next = NULL;
	return (p);
}

void ft_lstadd_back_arg(t_args **lst, t_args *new)
{
	t_args *last;

	if (!lst || !(*lst))
	{
		*lst = new;
		return;
	}
	last = ft_lstlast_arg(*lst);
	if (last)
		last->next = new;
}

t_args *init_struct_cmd(char **args)
{
    t_args *head = NULL;
    t_args *current = NULL;
    int i = 0;
    
    while (args[i])
    {
        t_args *new_node = malloc(sizeof(t_args));
        if (!new_node)
            return NULL;
        new_node->args = args[i];
        new_node->next = NULL;
        if (current)
            current->next = new_node;
        else
            head = new_node;
        current = new_node;
        i++;
    }
    return (head);
}

int main(int ac, char **av, char **env) {
    int i = 0;
	int	fd = 1;
	char *input;
	char *ss;
	char	**cmd_prt;
	t_args	*comd;

	get_env(env);
	while (1)
	{
		input = readline("\033[0;32mExecution =>> ");
		add_history (input);
		if (!input || input[0] == '\0')
			continue ;
		ss = epur_str(input);
		cmd_prt =  ft_split(ss, ' ');
		comd = init_struct_cmd(cmd_prt);
		check_builtin(comd, fd, glob.env_p);
		while(cmd_prt[i])
			free(cmd_prt[i++]);
		free(cmd_prt);
		free(input);
		free(ss);
		i = 0;
	}
    return 0;
}
