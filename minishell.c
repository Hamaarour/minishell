/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:25:47 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/07 17:53:08 by hamaarou         ###   ########.fr       */
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
	// t_str	str_s;
	// char	*in;
	t_env	*env_p;
	
	if (ac > 1)
	{
		printf("You cannot pass arguments to this program\n");
		exit(1);
	}
	get_env(&env_p, env);

	// printf("%s    %s\n", env_p->key, env_p->value);
	// printf("%s    %s\n", env_p->next->key, env_p->next->value);
	//system("leaks minishell");
	
	t_lexer *lexer;
    lexer = init_lexer("ls -l | grep main.c > $USER");
	lexer->env = env_p;
    t_token *token = get_next_token(lexer);
    while (token->type != t_EOF)
    {
        printf("Token type: %d, value: %s\n", token->type, token->val);
        token = get_next_token(lexer);
    }
	printf("%s\n", lexer->src);

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
			spliting_cmd(&str_s);
			//expand_var(&str_s, env_p);

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
	}*/

}
