#ifndef MINISHELL_H
# define MINISHELL_H

#include "../main.h"
#include "./libft/libft.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define FALSE 0;
#define TRUE 1;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

t_env *g_env;

/*
command func
*/
void ft_cd(t_string *arg);
void ft_echo(t_string *arg, char *op);
void ft_env(void);
void ft_exit(t_string *arg);
void ft_export(t_string *arg);
void ft_pwd(void);
void ft_unset(t_string *arg);

/*
tmp
*/
int		ft_strcmp(char *s1, char *s2);
void cmd_ctrl(t_inst *inst);
static void alter_pwd(void);

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

#endif