#ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft/libft.h"
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
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235

extern char **environ;

typedef struct s_inst t_inst;
typedef struct s_string t_string;
typedef struct s_env t_env;

struct s_string
{
	char *str;
	t_string *next;
};

typedef struct	s_redir
{
	int			argc;
	char		**argv;
	char		**cmds;
	char		*types;
}				t_redir;

struct s_inst
{
	char *inst;
	t_string *arg;
	int is_pipe; // 실행전 파싱 된것에서 찾아서 바꾼후 arg에서 지워 버리거나 아니면 아예 파싱 단계에서 | 발견시 1로 설정해주고
				 // arg에 따로 저장안해도 될듯합니다
	int pre_pipe; // ex) echo hello | exit, unset, export 등이 작동하면 안됨 하위프로세스가
				  // 상위 프로세스에 영향을 끼칠수없음 파싱단계 에서 처리 (X) 어차피 파이프 만들때 1로 바꿔주면됩니다
	int fds[2];   // 파이프함수 사용시 쓰이는 배열 입니다 
	int is_redir;
	t_redir *redir;
	t_inst *next;
};

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

/*
builtin func
*/
void ft_cd(t_string *arg);
void ft_echo(t_string *arg, char *op);
void ft_env(void);
void ft_exit(t_string *arg);
void ft_export(t_string *arg);
void ft_pwd(void);
void ft_unset(t_string *arg);

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
void	catch_error(char *msg, int errnum);
void error_msg_join(char *arg1, char *arg2);

/*
env related
*/
void edit_env_value(t_env *env, char *key, char *value);
t_env *get_env(t_env *env, char *key);
void del_env(char *key);
int check_valid_env_key(char *key);
static void alter_pwd(void);

/*
exec func
*/
int exec_builtin(t_inst *proc);
void exec_child_process(t_inst *proc, t_inst *next_proc);
void exec_pipe(t_inst *proc);
void exec_parent_process(t_inst *proc);

/*
exec util
*/
char *find_value(char *key, char **environ);
char *get_path(char *inst, char **environ);
void is_redir(t_inst *proc);
void is_pipe(t_inst *proc);

#endif