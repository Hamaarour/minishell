

#include "../minishell.h"

/*
	this function check if a dollar ($) found in the
	string if found return true else return false
*/

int	ft_find(char *str, char c)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);

	while (i < len)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
/*
check if a dollar ($) found in the string if found
return true(1) else return false(0)
*/
int	check_dollar(char *str, char dollar)
{
	if (ft_find(str, dollar) == 1)
		return (1);
	return (0);
}
/*
	this function find_var return the value of the envirment variable
	if the key is found in the envirment variables else return NULL
*/
char	*find_var(t_env *env_p, char *var)
{
	t_env	*tmp;

	tmp = env_p;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
