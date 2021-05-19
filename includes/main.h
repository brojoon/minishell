#ifndef MAIN_H
# define MAIN_H
# define DIVISOR 10
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 1024
# define CTRLD 4
# define KEY_LEFT 4479771
# define KEY_RIGHT 4414235
# define KEY_UP 4283163
# define KEY_DOWN 4348699
# define ESC 127

# include <termios.h>
# include <termcap.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
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
};
struct					s_env
{
	char				*key;
	char				*value;
	t_env				*next;
};

/*
** libft_01.c
*/
size_t						ft_strlen(const char *str);
int						nbr_length(int n);
int						ft_make_int(const char *ptr, int st, int ed, int sign);
int						ft_atoi(const char *nptr);
int						ft_putchar(int c);
/*
** libft_02.c
*/
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t len);
char					*ft_strnstr(char *big, char *little, size_t len);
/*
** libft_03.c
*/
void					ft_free_chunks(char **ret, int ret_st);
char					*ft_substr(const char *s, unsigned int start, size_t len);
int						ft_cnt_lines(char *s, char c);
char					**ft_split(char *s, char c);
int						ft_get_next_idx(char *buf, char c, int st);
/*
** ft_itoa.c
*/
char					*ft_rev_str(char *n, int size);
char					*ft_conv_int_to_char(unsigned int n, int sign);
char					*ft_itoa(int n);
/*
** ft_env_lst.c
*/
t_env					*ft_envinit(char *key, char *value);
void					set_genv(t_env **root, char **envp);
void					free_genv(t_env *env);
void					ft_envprint_all(t_env *root);
/*
** ft_env_lst_utils.c
*/
t_env					*ft_envfind(t_env *env, char *key);
void					ft_envfree(t_env *env);
void					ft_envremove(t_env **root, char *key);
void					ft_envadd_back(t_env **root, t_env *now);
void					ft_envchkandadd(t_env **root, t_env *now, int flag);
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
