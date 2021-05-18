#include "minishell.h"

void	print_export(t_env *envs)
{
	int		i;
	t_env	**sorted_envs;

	sorted_envs = quick_sort_init(envs);
	i = 0;
	while (sorted_envs[i])
	{
		ft_putstr_fd_j("declare -x ", 1);
		ft_putstr_fd_j(sorted_envs[i]->key, 1);
		if (sorted_envs[i]->value)
			ft_putstr_fd_j("=\"", 1);
		ft_putstr_fd_j(sorted_envs[i]->value, 1);
		if (sorted_envs[i]->value)
			ft_putchar_fd_j('\"', 1);
		ft_putchar_fd_j('\n', 1);
		i++;
	}
	free(sorted_envs);
	g_status = 0;
	return ;
}

int	is_valid_export(char *str)
{
	int	i;
	int key_value_sepa;

	i = -1;
	key_value_sepa = 0;
	if (ft_isdigit_j(str[0]) && !(str[0] == '_'))
		return (1);
	while (str[++i])
	{
		if (str[i] == '=')
			key_value_sepa = 1;
		else if ((str[i] == '+') && (str[i + 1] == '=')))
			i++;
		else (!(ft_isalnum_j(str[i])) && !(str[i] == '_') \
			&& !(str[i] == '=') && (!(str[i] == '+') && key_value_sepa))
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
		tmp2 = ft_strjoin_j(envs->value, tmp[i]);
		free(envs->value);
		envs->value = tmp2;
		free(tmp[i]);
		if (tmp[i + 1])
		{
			tmp2 = ft_strjoin_j(envs->value, "=");
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

	tmp = ft_split_j(str, '=');
	while (envs && envs->next && ft_strcmp_j(tmp[0], envs->key))
		envs = envs->next;
	if (!ft_strcmp_j(tmp[0], envs->key))
		free(envs->value);
	else
	{
		envs->next = (t_env *)malloc(sizeof(t_env));
		envs = envs->next;
		envs->key = tmp[0];
	}
	envs->value = ft_strdup_j("");
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
				err_msg = ft_strjoin_j(proc->inst, ": `");
				tmp = ft_strjoin_j(err_msg, proc->arg->str);
				free(err_msg);
				err_msg = ft_strjoin_j(tmp, "\'");
				catch_error(err_msg, "not a valid identifier");
				free(err_msg);
				g_status = 1;
				return ;
			}
			add_export(proc->arg->str, envs);
			proc->arg = proc->arg->next;
		}
	}
}
