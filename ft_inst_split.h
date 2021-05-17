#ifndef FT_INST_SPLIT_H
# define FT_INST_SPLIT_H
# include "ft_instlst.h"
/*
** ft_inst_split_utils.c
*/
char	**split_redirection(char *str, char **splitter);
int		check_red_error(char *inst);
int		is_fd(char *s);
void	echo_merge_args(t_inst **inst);
/*
** ft_inst_split_01.c
*/
int		hnadle_red_case_01(char **chunks, char *red, t_inst *inst, char *now);
int		handle_red_case_02(char **cmd, char *red, t_inst *inst, int *k);
int		handle_red_case_03(char **cmd, char *red, t_inst *inst, int *k);
int		handle_red_token(t_inst *inst, char **cmd, int *k);
/*
** ft_inst_split_02.c
*/
t_inst	*split_commands_subloop(char **pipe_chunks);
t_inst	*split_commands(char **semi_chunks, int line_cnt);
char	**inst_to_chunks(t_inst *inst);
/*
** ft_inst_split_03.c
*/
void	make_command_case_op(t_inst *inst, char *str);
void	make_command_case_arg(t_inst *inst, char *str);
int		make_command_case_01(t_inst *new_inst, char **space_chunks, int k);
t_inst	*make_command(char **space_chunks, int line_cnt);
#endif
