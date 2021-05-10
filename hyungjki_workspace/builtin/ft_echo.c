#include "../minishell.h"

void ft_echo(t_inst *proc, char *op)
{
	t_string *arg;

	arg = proc->arg;
	if(arg == NULL || arg->str == NULL)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		return ;
	}
	while(arg->next && arg->str)
	{
		ft_putstr_fd(arg->str, STDOUT_FILENO);
		arg = arg->next;
	}
	if (ft_strcmp(op, "-n") != 0)
		ft_putendl_fd("", STDOUT_FILENO);
	return ;
}

