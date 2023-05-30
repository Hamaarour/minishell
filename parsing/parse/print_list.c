
#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void print_cmd_data(t_data_cmd **cmd_data) 
{
	t_data_cmd * current = *cmd_data;	
	while (current  != NULL)
	{
		t_args *arg = current->args;
		while (arg != NULL)
		{
			printf("%s\n", arg->args);
			arg = arg->next;
		}
		printf("|*-*-*-*-* new_node *-*-*-*-*|\n");
		current = current->next;
	}
}