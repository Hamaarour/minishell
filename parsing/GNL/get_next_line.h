/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:29:01 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/29 08:47:22 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strchr_g(char *str);
char	*ft_strjoin_g(char **left_str, char *buff);
char	*ft_strdup_g(const char *s1);
char	*ft_substr_g(char const *s, unsigned int start, size_t len);
size_t	ft_strlen_g(const char *str);
char	*get_next_line(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
#endif
