#include "../../includes/minishell.h"

void ft_exit(t_inst *proc)
{
	t_string *arg;
	int i;

	i = 0;
	arg = proc->arg;
	while(arg && arg->str[i])
	{
		if (!ft_isdigit(arg->str[i]))
		{
			error_msg_join("exit: ", arg->str, "numeric argument required");
			exit(1) ;
		}
		i++;
	}
	if (arg && arg->next != NULL)
	{
		errno = 1;
		ft_putendl_fd("exit", STDOUT_FILENO);
		catch_error("exit", "too many arguments");
		return ;
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}