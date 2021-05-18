#include "minishell.h"

void	ft_exit(t_inst *proc)
{
	int		i;
	char	*err_msg;

	err_msg = "numeric argument required";
	i = 0;
	while (proc->arg && proc->arg->str[i])
	{
		if (!ft_isdigit_j(proc->arg->str[i]))
		{
			error_msg_join("exit: ", proc->arg->str, err_msg);
			g_status = 2;
			exit(1);
		}
		i++;
	}
	if (proc->arg && proc->arg->next != NULL)
	{
		errno = 1;
		ft_putendl_fd_j("exit", STDERR_FILENO);
		catch_error("exit", "too many arguments");
		g_status = 1;
		return ;
	}
	ft_putendl_fd_j("exit", STDOUT_FILENO);
	exit(0);
}
