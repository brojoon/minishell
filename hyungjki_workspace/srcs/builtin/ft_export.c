#include "minishell.h"

int get_g_env_size(t_env *g_env)
{
	int size;

	size = 0;
	while (g_env)
	{
		size++;
		g_env = g_env->next;
	}
	return (size);
}

void print_export(t_env *g_env)
{
	int i;
	t_env **sorted_g_env;
	sorted_g_env = quick_sort_init(g_env);

	i = 0;
	while(sorted_g_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sorted_g_env[i]->key, 1);
		if (sorted_g_env[i]->value)
			ft_putstr_fd("=\"", 1);
		ft_putstr_fd(sorted_g_env[i]->value, 1);
		if (sorted_g_env[i]->value)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	free(sorted_g_env);
	return ;
}

int is_valid_export(char *str)
{
	int i;

	i = -1;
	if (ft_isdigit(str[0]) && !(str[0] == '_'))
		return (1);
	while (str[++i])
	{	
		if (!(ft_isalnum(str[i])) && !(str[i] == '_') \
			&& !(str[i] == '='))
			return (1);
	}
	return (0);
}

void add_export(char *str, t_env *g_env)
{
	char **tmp;
	int i;

	i = 0; 
	while (g_env && g_env->next)
		g_env = g_env->next;
	g_env->next = (t_env *)malloc(sizeof(t_env *));
	g_env = g_env->next;
	tmp = ft_split(str, '=');
	g_env->key = tmp[0];
	g_env->value = ft_strdup("");
	while (tmp[++i])
	{
		g_env->value = ft_strjoin(g_env->value, tmp[i]);
		if (tmp[i + 1])
			g_env->value = ft_strjoin(g_env->value, "=");
	}
	g_env->next = NULL;
	free(tmp[i]);    
} 

void ft_export(t_inst *proc, t_env *g_env)
{
	if (proc->arg == NULL)
		print_export(g_env);
	else
	{
		while (proc->arg)
		{
			if (is_valid_export(proc->arg->str))
				return ;
			add_export(proc->arg->str, g_env);
			proc->arg = proc->arg->next;
		}
	}
}