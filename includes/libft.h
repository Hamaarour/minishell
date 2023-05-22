/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 20:26:04 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/21 22:08:55 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	*ft_calloc_p(size_t count, size_t size);
char	*ft_substr_p(char const *s, unsigned int start, size_t len);
char	**ft_split_p(char const *s, char sep);
int		ft_isalnum(int num);
char	*ft_strchr(char *str, int j);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strstr(const char *haystack, const char *needle);
int		ft_isalnum_original(int num);
char	*ft_itoa(int l);
void	ft_putendl_fd(char *s, int fd);

#endif
