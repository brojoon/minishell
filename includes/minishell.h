#ifndef MINISHELL_H
# define MINISHELL_H

#include "../srcs/exec/libft_j/libft_j.h"
# include <errno.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <termcap.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define FALSE 0
# define TRUE 1
# define RIGHT 4
# define LEFT 8
# define DRIGHT 12
# define BUFFER_SIZE 1024
# define CTRLD 4
# define KEY_LEFT 4479771
# define KEY_RIGHT 4414235
# define KEY_UP 4283163
# define KEY_DOWN 4348699
# define ESC 127
# define DIVISOR 10

int						g_status;
typedef struct s_string	t_string;
typedef struct s_inst	t_inst;
typedef struct s_env	t_env;
typedef struct s_cursor
{
	struct termios		term;
	char				*cm;
	char				*ce;
	int					hpos;
	int					vpos;
}	t_cursor;

struct s_string
{
	char				*str;
	t_string			*next;
};
struct					s_inst
{
	char				*inst;
	char				*option;
	t_string			*rd;
	t_string			*arg;
	t_inst				*next;
	t_inst				*child;
	int					fds[2];
};
struct					s_env
{
	char				*key;
	char				*value;
	t_env				*next;
};

void					print_status(void);
char					*get_prompt(void);
/*
builtin func
*/
void					ft_cd(t_inst *proc, t_env *envs);
void					ft_echo(t_inst *proc, char *op);
void					ft_env(t_env *envs);
void					ft_exit(t_inst *proc);
void					ft_export(t_inst *proc, t_env *envs);
void					ft_pwd(void);
void					ft_unset(t_inst *proc, t_env **envs);

/*
export func
*/
void					quick_sort_list(t_env **list, int first, int last);
void					swap(t_env **list, int i, int j);
t_env					**quick_sort_init(t_env *envs);
int						get_envs_size(t_env *envs);
void					print_export(t_env *envs);
int						is_valid_export(char *str);
void					add_export(char *str, t_env *envs);

/*
signal func
*/
void					set_signal(void);
void					handle_signal(int signo);

/*
error handle
*/
void					catch_error(char *inst, char *msg);
void					error_msg_join(char *arg1, char *arg2, char *arg3);

/*
env related
*/
void					edit_env_value(t_env *env, char *key, char *value);
t_env					*get_env(t_env *env, char *key);
void					del_env(char *key, t_env *envs);
int						check_valid_env_key(char *key);
void					alter_pwd(t_env *envs);
void					del_first(t_env **envs);

/*
exec func
*/
int						exec_builtin(t_inst *proc, t_env **envs);
void					exec_child_process(t_inst *proc, t_inst *child, t_env **envs);
void					exec_pipe(t_inst *proc, t_env **envs);
void					exec_parent_process(t_inst *proc, t_env **envs);

/*
redir func
*/
int						get_redir_type(t_string *rd);
int						get_redir_fd(t_inst *proc, int type);
int						exec_redir_right(t_inst *proc, t_env **envs);
int						exec_redir_dright(t_inst *proc, t_env **envs);
void					exec_redir_left(t_inst *proc, t_env **envs);
int						redir_skip_right(char *str);
int						redir_skip_left(char *str);
void					redir_exec(t_inst *proc, t_env **envs);
void					redir_init(t_inst *proc, t_env **envs);

/*
exec util
*/
char					*find_value(char *key, t_env *envs);
char					**envs_to_chunks(t_env *envs);
char					*get_path(char *inst, t_env *envs);
/*
** libft_01.c
*/
int						nbr_length(int n);
int						ft_putchar(int c);
void					ft_free_chunks(char **ret, int ret_st);
int						ft_cnt_lines(char *s, char c);
int						ft_get_next_idx(char *buf, char c, int st);
/*
** ft_env_lst.c
*/
t_env					*ft_envinit(char *key, char *value);
void					set_genv(t_env **root, char **envp);
void					free_genv(t_env *env);
/*
** ft_inst_split_utils.c
*/
char					**split_redirection(char *str, char **splitter);
int						check_red_error(char *inst);
int						is_fd(char *s);
void					echo_merge_args(t_inst **inst);
/*
** ft_inst_split_01.c
*/
int						hnadle_red_case_01(char **chunks, char *red,
							t_inst *inst, char *now);
int						handle_red_case_02(char **cmd, char *red,
							t_inst *inst, int *k);
int						handle_red_case_03(char **cmd, char *red,
							t_inst *inst, int *k);
int						handle_red_token(t_inst *inst, char **cmd, int *k);
/*
** ft_inst_split_02.c
*/
t_inst					*split_commands_subloop(char **pipe_chunks);
t_inst					*split_commands(char **semi_chunks, int line_cnt);
char					**inst_to_chunks(t_inst *inst);
/*
** ft_inst_split_03.c
*/
void					make_command_case_op(t_inst *inst, char *str);
void					make_command_case_arg(t_inst *inst, char *str);
int						make_command_case_01(t_inst *new_inst,
							char **space_chunks, int k);
t_inst					*make_command(char **space_chunks, int line_cnt);
/*
** ft_instlst.c
*/
void					ft_instadd_sibling(t_inst **root, t_inst *inst);
void					ft_instadd_child(t_inst **root, t_inst *inst);
void					ft_inst_free(t_inst *root);
t_inst					*ft_instinit(void);
/*
** ft_string_lst.c
*/
t_string				*ft_lstinit(char *s);
void					ft_lstfree(t_string *del);
t_string				*ft_lstremove(t_string **root, t_string *target);
void					ft_lstfree_all(t_string *root);
int						ft_lst_get_len(t_string *root);
/*
** ft_string_utils.c
*/
t_string				*ft_lstfind(t_string *root, char *target);
int						ft_lstcount(t_string *arg);
void					ft_lstadd_front(t_string **root, t_string *s);
void					ft_lstadd_after(t_string **root, t_string *s);
void					ft_lstadd_back(t_string **root, t_string *s);
/*
** get_next_line_utils.c
*/
int						ft_memset(char **line, size_t size);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
void					ft_resize_and_copy(char **line, char *buf,
							int st, int ed);
char					*ft_strdup(char *str);
int						recover_term(t_cursor *cursor);
/*
** get_next_line.c
*/
int						ft_while_loop(char **line, char *buf, char **buf_ref);
int						ft_proc_buf_ref(char **line, char **buf_ref);
char					*replace_str(char **buf, int st, int ed, char *to);
int						get_next_line_subloop(int fd, char *prompt,
							t_cursor *cursor, char **buf);
int						get_next_line(int fd, char **line,
							char *prompt, t_cursor *cursor);
/*
** ft_cursor.c
*/
int						cursor_mvleft(t_cursor *cursor, int hpos_min);
int						cursor_mvright(t_cursor *cursor, int hpos_max);
int						cursor_erase(t_cursor *cursor, int hpos_min, char *buf);
int						proc_cursor(t_cursor *cursor, int flag,
							int hpos_min, char *buf);
void					update_cursor_pos(t_cursor *cursor);
/*
** ft_quotes_utils.c
*/
int						cnt_quotes(char *str, char c, int *meta_arr);
char					*encap_quotes(char *str, char quote);
char					*decap_quotes(char *str, char *quote);
int						*get_meta_arr(char *str);
/*
** ft_quotes_01.c
*/
int						quotes_sub_loop(char **buf, int **meta_arr,
							char target, t_cursor *cursor);
void					handle_quotes_subcase(char **buf,
							t_string **const_strings, int **meta_arr, int *st);
void					handle_quotes(char **buf, t_string **const_strings,
							t_cursor *cursor);
void					proc_quotes(t_env *root, char **now);
/*
** ft_quotes_02.c
*/
void					proc_consts(t_env *root, t_string **consts);
int						get_ori_consts_subloop(char **arg,
							t_string **const_now);
void					get_ori_consts(t_string *str, t_inst **inst_now);
void					proc_inst_metachar_subloop(t_env *root,
							t_inst *children);
void					proc_inst_metachar(t_env *root, t_inst **insts);
/*
** ft_quotes_03.c
*/
int						proc_metachar_case_single(char **out, char *s,
							int *meta_arr, int *st);
int						proc_metachar_case_dollar(char **out, char *s,
							t_env *root, int *st);
int						proc_metachar_subloop(char **out, t_env *root,
							char *s, int *st);
char					*proc_metachar(t_env *root, char *s);
/*
**	ft_error.c
*/
int						ft_write_and_ret(char *inst, char *msg, int ret);
#endif