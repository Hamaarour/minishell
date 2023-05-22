
#include "../../includes/parsing.h"

//this function print the linked list of the tokens
void print_cmd_data(t_data_cmd **cmd_data) 
{
	while ((*cmd_data) != NULL)
	{
		t_args *arg = (*cmd_data)->args;
		while (arg != NULL)
		{
			printf("%s\n", arg->args);
			arg = arg->next;
		}
		printf("|*-*-*-*-* new_node *-*-*-*-*|\n");
		(*cmd_data) = (*cmd_data)->next;
	}
}