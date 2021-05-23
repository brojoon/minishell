#include "minishell.h"

int	get_redir_type(t_string *rd)
{
	int	i;

	i = 0;
	if (rd && rd->str)
	{
		while (rd->str[i] && !(ft_strchr("><", rd->str[i])))
			i++;
		if (rd->str[i])
		{
			if (rd->str[i] == '>')
			{
				if (rd->str[i + 1] == '>')
					return (DRIGHT);
				return (RIGHT);
			}
			else
				return (LEFT);
		}
	}
	return (0);
}

int	get_redir_fd(t_string *rd, int type)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (ft_isdigit(rd->str[i]))
	{
		num = num * 10 + (rd->str[i] - '0');
		i++;
	}
	if (i == 0)
		return (type);
	return (num);
}
