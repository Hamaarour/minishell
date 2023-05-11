/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:37:34 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/07 18:47:26 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

#ifndef GLOBAL_VARIABLE_H
# define GLOBAL_VARIABLE_H

int EXIST_STATUS;

#endif

int		ft_strcmp(const char *s1, const char *s2);
void	echo(char **input, int outf);
void	pwd(char **input, int fd);
char	*epur_str(char* s);


typedef struct cmd {
    char* value;
    struct cmd* next;
} t_cmd;

#endif