#include "minishell.h"

int	get_next_line_sub(char *prompt, char **buf, int *clean_flag)
{
	*clean_flag = 0;
	if (g_bash.clean == 0)
		write(0, prompt, ft_strlen(prompt));
	if (g_bash.clean == 1)
	{
		g_bash.clean = 0;
		if (**buf == '\n')
			*clean_flag = 1;
	}
	return (*clean_flag);
}

int	get_next_line_sub01(char **buf, char **line, char **buf_ref)
{
	char		*temp;

	ft_memset(buf, BUFFER_SIZE + 1);
	if (*buf_ref)
	{
		if (g_bash.clean == 0)
		{
			if (ft_proc_buf_ref(line, buf_ref))
				return (1);
		}
		else
		{
			temp = 0;
			ft_proc_buf_ref(&temp, buf_ref);
			ft_strlcpy(*buf, temp, ft_strlen(temp) + 1);
			free(temp);
		}
	}
	return (0);
}

int	get_next_line_whilesub(int rd, char **buf_ref, char **buf)
{
	if (rd == 9999)
	{
		free(*buf);
		return (9999);
	}
	else if (g_bash.clean == 1)
	{
		ft_resize_and_copy(buf_ref, (*buf + ft_strlen(*buf) - 1), 0, 1);
		ft_memclean(buf, ft_strlen(*buf));
		return (1);
	}
	return (0);
}
