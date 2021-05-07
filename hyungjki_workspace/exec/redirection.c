#include "../minishell.h"

int get_redir_type(t_string *arg)
{
	int i;

	while (arg)
	{
		while (arg->str[i])
		{
			if ('>' == arg->str[i])
			{
				if ('>' == arg->str[i + 1])
					return (DRIGHT);
				return (RIGHT);
			}
			else if ('<' == arg->str[i])
				return (LEFT);
			i++;
		}
		arg = arg->next;
	}
	return (0);
}
