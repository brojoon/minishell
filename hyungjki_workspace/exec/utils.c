#include "../minishell.h"

char *find_value(char *key, char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], key, ft_strlen(key)))
		{
			if (environ[i][ft_strlen(key)] == '=')
				return (environ[i] + ft_strlen(key) + 1);
		}
		i++;
	}
	return ("");
}

char *get_path(char *inst, char **environ)
{
	int			i;
	char		*tmp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	tmp = find_value("PATH", environ);
	paths = ft_split(tmp, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin("/", inst);
		new_path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (stat(new_path, &s) == 0)
			return (new_path);
		free(new_path);
	}
	return (ft_strdup(inst));
}

void is_redir(t_inst *proc)
{
	t_string *arg;
	while(proc)
	{
		if (proc->arg)
		{
			arg = proc->arg;
			while (arg)
			{
				if (ft_strchar(arg->str, '<') || ft_strchar(arg->str, '>'))
				{
					proc->is_redir = 1;
					break;
				}
				arg = arg->next;
			}
		}
		proc = proc->next;
	}
}

void is_pipe(t_inst *proc)
{
	t_string *arg;

	while(proc)
	{
		if (proc->arg)
		{
			arg = proc->arg;
			while (arg)
			{
				if (ft_strchar(arg->str, '|'))
				{
					proc->is_pipe = 1;
					break;
				}
				arg = arg->next;
			}
		}
		proc = proc->next;
	}
}

