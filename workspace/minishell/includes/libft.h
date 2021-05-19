#ifndef LIBFT_H
# define LIBFT_H
# define DIVISOR 10
# include <unistd.h>
# include <stdlib.h>

/*
** libft_01.c
*/
int		ft_strlen(char *str);
int		nbr_length(int n);
int		ft_make_int(const char *ptr, int st, int ed, int sign);
int		ft_atoi(const char *nptr);
int		ft_putchar(int c);
/*
** libft_02.c
*/
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
int		ft_strncmp(char *s1, char *s2, int len);
char	*ft_strnstr(char *big, char *little, size_t len);
/*
** libft_03.c
*/
void	ft_free_chunks(char **ret, int ret_st);
char	*ft_substr(char *s, int start, int len);
int		ft_cnt_lines(char *s, char c);
char	**ft_split(char *s, char c);
int		ft_get_next_idx(char *buf, char c, int st);
/*
** ft_itoa.c
*/
char	*ft_rev_str(char *n, int size);
char	*ft_conv_int_to_char(unsigned int n, int sign);
char	*ft_itoa(int n);
#endif
