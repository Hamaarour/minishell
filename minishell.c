/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/05 15:51:48 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	main(int ac, char **av, char **env)
{
	(void)env;
	(void)av;
	t_str	lexer;
	char	*in;
	t_env	*env_p;

	if (ac > 1)
	{
		printf("You cannot pass arguments to this program\n");
		exit(1);
	}
	get_env(&env_p, env);
	while (1)
	{
		in = readline("[minishell~$]->> ");
		if (in)
		{
			add_history(in);
			lexer.str = in;
			check_pipes(&lexer);
			check_qutes(lexer.str);
			check_syntaxe(lexer.str);

		}
		free(in);

	}




}
