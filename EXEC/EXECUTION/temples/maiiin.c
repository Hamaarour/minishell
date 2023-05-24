/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maiiin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:15:20 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/24 01:15:22 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_new_env(char *s)
{
	t_env	*a;
	t_list	*l;
	int		i;

	i = ft_strlen(s);
	l = g_data.env;
	while (l)
	{
		a = (t_env *) l->content;
		if (ft_strncmp(s, a->key, i) == 0)
			return (a->value);
		l = l->next;
	}
	return (0);
}

int	set_signals(char *str, t_list **tokens)
{
	if (str == NULL)
		exit(0);
	if (!(str[0] != '\0'))
		return (1);
	add_history(str);
	*tokens = lexer(str);
	if (check_syntax(*tokens))
	{
		deallocate(*tokens);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*tokens;
	t_list	*cmd;

	(void)ac;
	(void)av;
	g_data.env = get_env(env);
	cmd = NULL;
	g_data.index = 0;
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline("➜ minishell ");
		if (set_signals(str, &tokens))
		{
			free(str);
			continue ;
		}
		cmd = fill_command(tokens);
		g_data.exit_status = 0;
		start(cmd);
		deallocate(tokens);
		free(str);
	}
	return (0);
}
