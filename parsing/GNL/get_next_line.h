/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:29:01 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/23 17:00:15 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strchr_G(char *str);
char	*ft_strjoin_G(char **left_str, char *buff);
char	*ft_strdup_G(const char *s1);
char	*ft_substr_G(char const *s, unsigned int start, size_t len);
size_t	ft_strlen_G(const char *str);
char	*get_next_line(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
#endif
