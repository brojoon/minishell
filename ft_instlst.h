#ifndef FT_INSTLST_H
# define FT_INSTLST_H
# include "ft_string_lst.h"
// 1개 명령어 struct
typedef struct s_inst	t_inst;
struct					s_inst
{
	char				*inst;
	char				*option;
	t_string			*rd;
	t_string			*arg;
	t_inst				*next;
	t_inst				*child;
};

void	ft_instadd_sibling(t_inst **root, t_inst *inst);
void	ft_instadd_child(t_inst **root, t_inst *inst);
void	ft_inst_free(t_inst *root);
t_inst	*ft_instinit(void);
#endif
