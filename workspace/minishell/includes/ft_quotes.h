#ifndef FT_QUOTES_H
# define FT_QUOTES_H
# include "ft_env_lst.h"
# include "ft_instlst.h"
int	g_status;
/*
** ft_quotes_utils.c
*/
int		cnt_quotes(char *str, char c, int *meta_arr);
char	*encap_quotes(char *str, char quote);
char	*decap_quotes(char *str, char *quote);
int		*get_meta_arr(char *str);
/*
** ft_quotes_01.c
*/
int		quotes_sub_loop(char **buf, int **meta_arr,
			char target, t_cursor *cursor);
void	handle_quotes_subcase(char **buf, t_string **const_strings,
			int **meta_arr, int *st);
void	handle_quotes(char **buf, t_string **const_strings, t_cursor *cursor);
void	proc_quotes(t_env *root, char **now);
/*
** ft_quotes_02.c
*/
void	proc_consts(t_env *root, t_string **consts);
int		get_ori_consts_subloop(char **arg, t_string **const_now);
void	get_ori_consts(t_string *str, t_inst **inst_now);
void	proc_inst_metachar_subloop(t_env *root, t_inst *children);
void	proc_inst_metachar(t_env *root, t_inst **insts);
/*
** ft_quotes_03.c
*/
int		proc_metachar_case_single(char **out, char *s, int *meta_arr, int *st);
int		proc_metachar_case_dollar(char **out, char *s, t_env *root, int *st);
int		proc_metachar_subloop(char **out, t_env *root, char *s, int *st);
char	*proc_metachar(t_env *root, char *s);
#endif
