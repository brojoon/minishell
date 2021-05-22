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
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(sorted_envs[i]->value, 1);
			ft_putchar_fd('\"', 1);
		}
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
	int	key_value_sepa;

	i = 0;
	key_value_sepa = 0;
	g_status = 1;
	if (!ft_isalpha(str[0]) && !(str[0] == '_'))
		return (1);
	while (str[++i])
	{
		if (str[i] == '=')
			key_value_sepa = 1;
		else if (!(ft_isalnum(str[i])) && !(str[i] == '_') && \
		!(str[i] == '=') && (!(str[i] == '+') || !key_value_sepa) && \
		(!(str[i] == '+') || !(str[i + 1] == '=')))
			return (1);
	}
	g_status = 0;
	return (0);
}

void	check_export(char *str, t_env *envs)
{
	int		i;
	int		is_sepa;

	is_sepa = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=' && str[i + 1] == '\0' && !is_sepa)
		{
			add_export(str, envs);
			return ;
		}
		if (str[i] == '=')
			is_sepa = 1;
		if (str[i] == '+' && str[i + 1] == '=' && !is_sepa)
		{
			append_export(str, envs);
			return ;
		}
	}
	if (!is_sepa)
		value_is_null(str, envs);
	else
		add_export(str, envs);
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
				err_msg = ft_strjoin(proc->inst, ": `");
				tmp = ft_strjoin(err_msg, proc->arg->str);
				free(err_msg);
				err_msg = ft_strjoin(tmp, "\'");
				catch_error(err_msg, "not a valid identifier");
				free(err_msg);
				free(tmp);
				return ;
			}
			check_export(proc->arg->str, envs);
			proc->arg = proc->arg->next;
		}
	}
}
