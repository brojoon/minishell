#include "../minishell.h"

void ft_exit(t_inst *proc)
{
	t_string *arg;
	char *msg;
	int i;

	arg = proc->arg;
	ft_putendl_fd("exit", STDOUT_FILENO);
	while(arg->str[i])
	{
		if (!ft_isdigit(arg->str[i]))
			error_msg_join("exit: ", arg->str, errno);
		i++;
	}
	if (arg->next != NULL)
	{
		errno = 1;
		catch_error("exit", "too many arguments");
	}
}