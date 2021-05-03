#include "../minishell.h"	

void cmd_ctrl(t_inst *inst)
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
