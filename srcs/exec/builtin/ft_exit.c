#include "minishell.h"

void	exit_number(t_inst *proc, t_cursor *cursor)
{
	int		i;

	i = 0;
	if (proc->arg->str)
		i = atoi(proc->arg->str);
	recover_term(cursor);
	printf("exit: %d", i);
	exit(i);
}

void	ft_exit(t_inst *proc, t_cursor *cursor)
{
	int		i;

	i = 0;
	while (proc->arg && proc->arg->str[i])
	{
		if (!ft_isdigit(proc->arg->str[i]))
		{
			error_msg_join("exit: ", proc->arg->str, ERR_NAR);
			g_status = 2;
			recover_term(cursor);
			exit(2);
		}
		i++;
	}
	if (proc->arg && proc->arg->next != NULL)
	{
		errno = 1;
		ft_putendl_fd("exit", STDERR_FILENO);
		catch_error("exit", ERR_TMA);
		g_status = 1;
		return ;
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit_number(proc, cursor);
}
