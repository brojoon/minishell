#include "minishell.h"	

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else if (s1[i] == '\0')
		return (-1);
	else
		return (1);
}

static void cmd_ctrl(t_inst *inst)
{
	if (ft_strcmp(inst->inst, "cd") == 0)
		ft_cd(inst->arg);
	else if (ft_strcmp(inst->inst, "echo") == 0)
		ft_echo(inst->arg, inst->option);
	else if (ft_strcmp(inst->inst, "env") == 0)
		ft_env();
	else if (ft_strcmp(inst->inst, "exit") == 0)
		ft_exit(inst->arg);
	else if (ft_strcmp(inst->inst, "export") == 0)
		ft_export(inst->arg);
	else if (ft_strcmp(inst->inst, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(inst->inst, "unset") == 0)
		ft_unset(inst->arg);
}

g_env *get_env_list(void)
{
	static g_env *env_list = NULL;

	return (&env_list);
}