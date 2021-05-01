#ifndef MINISHELL_H
# define MINISHELL_H

#include "../main.h"
#include "./libft/libft.h"
#include <stdio.h>
#include <string.h>

#define FALSE 0;
#define TRUE 1;

typedef struct g_env
{
	char *key;
	char *value;
	struct g_env *next;
} g_env;

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
static void cmd_ctrl(t_inst *inst);
g_env *get_env_list(void);

#endif