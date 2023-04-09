/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/09 23:13:04 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	t_str	str_s;
	char	*in;
	t_env	*env_p;

	env_p = NULL;
	if (ac > 1)
	{
		printf("You cannot pass arguments to this program\n");
		exit(1);
	}
	get_env(&env_p, env);

	// printf("%s    %s\n", env_p->key, env_p->value);
	// printf("%s    %s\n", env_p->next->key, env_p->next->value);
	//system("leaks minishell");

	while (1)
	{
		in = readline("[minishell~$]->> ");
		if (in)
		{
			add_history(in);
			str_s.str = in;
			check_pipes(&str_s);
			check_qutes(str_s.str);
			check_syntaxe(str_s.str);
			spliting_cmd(&str_s);
			expand_var(&str_s, env_p);
			print_str(str_s.splited_str);
			int i = 0;
			while (str_s.splited_str[i])
			{
				free(str_s.splited_str[i]);
				str_s.splited_str[i] = NULL;
				i++;
			}
			free(str_s.splited_str);
			//system("leaks minishell");
		}
		//system("leaks minishell");
		free(in);
	}

}
