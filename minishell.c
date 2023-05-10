/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/10 12:40:14 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

void	print_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("\n");
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	t_env	*env_p;
	t_lexer *lexer;
	t_token *token;
	
	g_gob.ex_status = 0;
	if (ac > 1)
	{
		ft_putendl_fd("You cannot pass arguments to this program", 2);
		exit(EXIT_FAILURE);
	}
	get_env(&env_p, env);
    lexer = init_lexer("ls -l |   \"$USER\" >>");
	lexer->env = env_p;
    token = get_next_token(lexer);
	
    while (token->type != t_EOF)
    {
        printf("Token ( %d , %s)\n", token->type, token->val);
		free(token->val);
		free(token);
        token = get_next_token(lexer);
    }
	//system("leaks minishell");

	
	/*
	while (1)
	{
		in = readline("[minishell~$]->> ");
		if (in)
		{
			add_history(in);
			str_s.str = in;
			check_pipes(&str_s);
			check_syntaxe(str_s.str);
			//system("leaks minishell");
		}
		//system("leaks minishell");
		free(in);
	}*/

}
