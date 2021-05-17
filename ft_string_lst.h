#ifndef FT_STRING_LST_H
# define FT_STRING_LST_H
# include "get_next_line.h"

typedef struct s_string	t_string;
struct s_string
{
	char				*str;
	t_string			*next;
};

/*
** ft_string_lst.c
*/
t_string	*ft_lstinit(char *s);
void		ft_lstfree(t_string *del);
t_string	*ft_lstremove(t_string **root, t_string *target);
void		ft_lstfree_all(t_string *root);
int			ft_lst_get_len(t_string *root);
/*
** ft_string_utils.c
*/
t_string	*ft_lstfind(t_string *root, char *target);
int			ft_lstcount(t_string *arg);
void		ft_lstadd_front(t_string **root, t_string *s);
void		ft_lstadd_after(t_string **root, t_string *s);
void		ft_lstadd_back(t_string **root, t_string *s);
#endif
