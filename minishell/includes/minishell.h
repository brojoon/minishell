#ifndef MINISHELL_H
# define MINISHELL_H

#include "../srcs/exec/libft_j/libft_j.h"
#include "main.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>

# define FALSE 0
# define TRUE 1
# define RIGHT 4
# define LEFT 8
# define DRIGHT 12

/*
전역 변수 // 
*/
extern int g_status;
void print_status(void);

/*
builtin func
*/
void ft_cd(t_inst *proc, t_env *envs);
void ft_echo(t_inst *proc, char *op);
void ft_env(t_env *envs);
void ft_exit(t_inst *proc);
void ft_export(t_inst *proc, t_env *envs);
void ft_pwd(void);
void ft_unset(t_inst *proc, t_env **envs);

/*
export func
*/
void quick_sort_list(t_env **list, int first, int last);
void swap(t_env **list, int i, int j);
t_env **quick_sort_init(t_env *envs);
int get_envs_size(t_env *envs);
void print_export(t_env *envs);
int is_valid_export(char *str);
void add_export(char *str, t_env *envs);

/*
signal func
*/
void set_signal(void);
void handle_signal(int signo);

/*
error handle
*/
void	catch_error(char *inst, char *msg);
void error_msg_join(char *arg1, char *arg2, char *arg3);

/*
env related
*/
void edit_env_value(t_env *env, char *key, char *value);
t_env *get_env(t_env *env, char *key);
void del_env(char *key, t_env *envs);
int check_valid_env_key(char *key);
void alter_pwd(t_env *envs);
void	del_first(t_env **envs);

/*
exec func
*/
int exec_builtin(t_inst *proc, t_env **envs);
void exec_child_process(t_inst *proc, t_inst *child, t_env **envs);
void exec_pipe(t_inst *proc, t_env **envs);
void exec_parent_process(t_inst *proc, t_env **envs);

/*
redir func
*/
int get_redir_type(t_string *rd);
int get_redir_fd(t_inst *proc, int type);
int exec_redir_right(t_inst *proc, t_env **envs);
int exec_redir_dright(t_inst *proc, t_env **envs);
void	exec_redir_left(t_inst *proc, t_env **envs);
int redir_skip_right(char *str);
int redir_skip_left(char *str);
void redir_exec(t_inst *proc, t_env **envs);
void redir_init(t_inst *proc, t_env **envs);

/*
exec util
*/
char *find_value(char *key, t_env *envs);
char **envs_to_chunks(t_env *envs);
char *get_path(char *inst, t_env *envs);

#endif