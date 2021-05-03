#include "../minishell.h"

void ft_exit(t_string *arg)
{
	t_string *node;
	char *msg;
	int i;

	node = arg;
	ft_putendl_fd("exit", STDOUT_FILENO);
	while(node->str[i])
	{
		if (!ft_isdigit(node->str[i]))
			error_msg_join("exit: ", node->str);
		i++;
	}
	if (node->next != NULL)
	{
		errno = 1;
		catch_error("exit", errno);
	}
}