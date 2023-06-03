/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:17:13 by zjaddad           #+#    #+#             */
/*   Updated: 2023/06/03 17:17:04 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct atoi
{
	int					i;
	unsigned long long	result;
	int					sign;

}	t_ati;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
int		ft_lstsize(t_list *lst);
int		ft_isalpha(int c);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isprint(int pr);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t lent);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strrchr(const char *str, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_strlcpy(char *d, const char *s, size_t d_size);
size_t	ft_strlcat(char *dt, const char *sc, size_t size_d);
int		ft_memcmp(const void *str1, const void *str2, size_t lent);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_atoi(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *hyst, const char *ndl, size_t lent);
void	*ft_calloc(size_t n, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *setr);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc_p(size_t count, size_t size);
char	*ft_substr_p(char const *s, unsigned int start, size_t len);
char	**ft_split_p(char const *s, char sep);
void	*ft_calloc_p(size_t count, size_t size);
char	*ft_substr_p(char const *s, unsigned int start, size_t len);
char	**ft_split_p(char const *s, char sep);

#endif
