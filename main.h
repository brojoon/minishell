#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <signal.h>
#include "get_next_line.h"

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

t_string *ft_lstinit(char *s);
int ft_lstcount(t_string *arg);
int ft_cd(t_env *env, t_inst *inst);
int ft_pwd(void);
int ft_ls(t_inst *inst);
char *ft_strchr(char *s, int c);
char *ft_strnstr(char *big, char *little, size_t len);
int ft_cnt_lines(char *s, char c);
int ft_export(t_env *env, t_inst *inst);
char **ft_split(char *s, char c);
int ft_strncmp(char *s1, char *s2, int len);
void ft_envadd_back(t_env **root, t_env *now);
t_env *ft_envinit(char *key, char *value);
t_env *ft_envfind(t_env *env, char *key);
void ft_free_chunks(char **ret, int ret_st);
void ft_envchkandadd(t_env **root, t_env *now, int flag);
void ft_envprint_all(t_env *root);
void ft_envremove(t_env **root, char *key);
int ft_unset(t_env *env, t_inst *inst);
int ft_env(t_env *env, t_inst *inst);
int ft_chk_key(char *s);
int ft_chk_export(t_inst *inst);
char *ft_substr(char *s, int start, int len);
int ft_echo(t_inst *inst);
