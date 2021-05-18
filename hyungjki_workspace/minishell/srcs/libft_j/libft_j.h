/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 02:56:21 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/20 00:27:27 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

int					ft_atoi_j(const char *str);
char				*ft_itoa_j(int n);
int					ft_isalnum_j(int c);
int					ft_isalpha_j(int c);
int					ft_isascii_j(int c);
int					ft_isdigit_j(int c);
int					ft_isprint_j(int c);
size_t				ft_strlcat_j(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy_j(char *dst, const char *src, size_t size);
size_t				ft_strlen_j(const char *s);
char				*ft_strchr_j(const char *s, int c);
char				*ft_strdup_j(const char *s1);
char				*ft_strjoin_j(char const *s1, char const *s2);
char				**ft_split_j(char const *s, char c);
char				*ft_strmapi_j(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp_j(const char *s1, const char *s2, size_t size);
char				*ft_strnstr_j(const char *big, const char *little,
						size_t len);
int					ft_strcmp_j(char *s1, char *s2);
char				*ft_strrchr_j(const char *s, int c);
char				*ft_strtrim_j(char const *s1, char const *set);
char				*ft_substr_j(char const *s, unsigned int start, size_t len);
int					ft_tolower_j(int c);
int					ft_toupper_j(int c);

void				*ft_memchr_j(const void *s, int c, size_t n);
int					ft_memcmp_j(const void *s1, const void *s2, size_t n);
void				*ft_memcpy_j(void *dst, const void *src, size_t len);
void				*ft_memccpy_j(void *dst, const void *src, int c, size_t n);
void				*ft_memmove_j(void *dst, const void *src, size_t len);
void				*ft_memset_j(void *b, int c, size_t len);
void				ft_bzero_j(void *s, size_t n);
void				*ft_calloc_j(size_t count, size_t size);

void				ft_putchar_fd_j(char c, int fd);
void				ft_putendl_fd_j(char *s, int fd);
void				ft_putnbr_fd_j(int n, int fd);
void				ft_putstr_fd_j(char *s, int fd);

typedef struct s_list2
{
	void			*content;
	struct s_list2	*next;
}				t_list1;

void				ft_lstadd_front_j(t_list1 **lst, t_list1 *node);
void				ft_lstadd_back_j(t_list1 **lst, t_list1 *node);
void				ft_lstclear_j(t_list1 **lst, void (*del)(void *));
void				ft_lstdelone_j(t_list1 *lst, void (*del)(void *));
void				ft_lstiter_j(t_list1 *lst, void (*f)(void *));
int					ft_lstsize_j(t_list1 *lst);
t_list1				*ft_lstnew_j(void *content);
t_list1				*ft_lstlast_j(t_list1 *lst);
t_list1				*ft_lstmap_j(t_list1 *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
