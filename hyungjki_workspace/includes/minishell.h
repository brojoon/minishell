#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <termios.h>
#include <termcap.h>
#include <signal.h>

# define FALSE 0
# define TRUE 1
# define RIGHT 4
# define LEFT 8
# define DRIGHT 12
# define BACKSPACE 127
# define KEY_UP 4283163
# define KEY_DOWN 4348699
# define KEY_RIGHT 4414235
# define KEY_LEFT 4479771

// 1개 명령어 struct
typedef struct s_inst t_inst;
typedef struct s_string t_string;
typedef struct s_env t_env;
struct s_inst
{
	char *inst;
	char *option;
	t_string *rd;
	t_string *arg;
	t_inst *next;
	t_inst *child;
	int fds[2];
};

struct s_string
{
	char *str;
	t_string *next;
};

struct s_env
{
	char *key;
	char *value;
	t_env *next;
};

typedef struct		s_hist
{
	char			*inst;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

/*
builtin func
*/
void ft_cd(t_inst *proc, t_env *g_env);
void ft_echo(t_inst *proc, char *op);
void ft_env(t_env *g_env);
void ft_exit(t_inst *proc);
void ft_export(t_inst *proc, t_env *g_env);
void ft_pwd(void);
void ft_unset(t_inst *proc, t_env *g_env);

/*
signal func
*/
void set_signal(void);
void handle_signal(int signo);

/*
tmp
*/


/*
error handle
*/
void	catch_error(char *inst, char *msg);
void error_msg_join(char *arg1, char *arg2, int errnum);

/*
env related
*/
void edit_env_value(t_env *env, char *key, char *value);
t_env *get_env(t_env *env, char *key);
void del_env(char *key, t_env **g_env);
int check_valid_env_key(char *key);
void alter_pwd(t_env *g_env);

/*
exec func
*/
int exec_builtin(t_inst *proc, t_env *g_env);
void exec_child_process(t_inst *proc, t_inst *child, t_env *g_env);
void exec_pipe(t_inst *proc, t_env *g_env);
void exec_parent_process(t_inst *proc, t_env *g_env);

/*
redir func
*/
int get_redir_type(t_string *rd);
int get_redir_fd(t_inst *proc, int type);
int exec_redir_right(t_inst *proc, t_env *g_env);
int exec_redir_dright(t_inst *proc, t_env *g_env);
int	exec_redir_left(t_inst *proc, t_env *g_env);
int redir_skip_right(char *str);
int redir_skip_left(char *str);
void redir_exec(t_inst *proc, t_env *g_env);
void redir_init(t_inst *proc, t_env *g_env);

/*
exec util
*/
char *find_value(char *key, t_env *g_env);
char *get_path(char *inst, t_env *g_env);
void is_redir(t_inst *proc);
void is_pipe(t_inst *proc);

#endif