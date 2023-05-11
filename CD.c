/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:25:04 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/07 03:52:59 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int main() {
 
// changing the current
// working directory(cwd)
// to /usr
if (chdir("/usr") != 0)
    perror("chdir() to /usr failed");
 
// changing the cwd to /tmp
if (chdir("/tmp") != 0)
    perror("chdir() to /temp failed");
 
// there is no /error
// directory in my pc
if (chdir("/error") != 0)
 
    // so chdir will return -1
    perror("chdir() to /error failed");
 
	return 0;
}
