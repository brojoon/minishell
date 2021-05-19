#include "minishell.h"

void	print_export(t_env *envs)
{
	int		i;
	t_env	**sorted_envs;

	sorted_envs = quick_sort_init(envs);
	i = 0;
	while (sorted_envs[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sorted_envs[i]->key, 1);
		if (sorted_envs[i]->value)
			ft_putstr_fd("=\"", 1);
		ft_putstr_fd(sorted_envs[i]->value, 1);
		if (sorted_envs[i]->value)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	free(sorted_envs);
	g_status = 0;
	return ;
}

int	is_valid_export(char *str)
{
	int	i;

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

void	handle_value(char **tmp, t_env *envs)
{
	int		i;
	char	*tmp2;

	i = 0;
	while (tmp[++i])
	{
		tmp2 = ft_strjoin(envs->value, tmp[i]);
		free(envs->value);
		envs->value = tmp2;
		free(tmp[i]);
		if (tmp[i + 1])
		{
			tmp2 = ft_strjoin(envs->value, "=");
			free(envs->value);
			envs->value = tmp2;
		}
	}
	envs->next = NULL;
	free(tmp[i]);
}

void	add_export(char *str, t_env *envs)
{
	char	**tmp;

	while (envs && envs->next)
		envs = envs->next;
	envs->next = (t_env *)malloc(sizeof(t_env));
	envs = envs->next;
	tmp = ft_split(str, '=');
	envs->key = tmp[0];
	envs->value = ft_strdup("");
	handle_value(tmp, envs);
	free(tmp);
	g_status = 0;
}

void	ft_export(t_inst *proc, t_env *envs)
{
	char	*err_msg;
	char	*tmp;

	if (proc->arg == NULL)
		print_export(envs);
	else
	{
		while (proc->arg)
		{
			if (is_valid_export(proc->arg->str))
			{
				g_status = 1;
				err_msg = ft_strjoin(proc->inst, ": `");
				tmp = ft_strjoin(err_msg, proc->arg->str);
				free(err_msg);
				err_msg = ft_strjoin(tmp, "\'");
				catch_error(err_msg, "not a valid identifier");
				free(err_msg);
				return ;
			}
			add_export(proc->arg->str, envs);
			proc->arg = proc->arg->next;
		}
	}
}
