#include "../minishell.h"

char *find_value(char *key, t_env *g_env)
{
	int	i;

	i = 0;
	while (g_env)
	{
		if (!ft_strcmp(g_env->key, key))
			return (g_env->value);
		g_env = g_env->next;
	}
	return ("");
}

char *get_path(char *inst, t_env *g_env)
{
	int	 i;
	char *tmp;
	char *new_path;
	char **paths;
	struct stat	s;

	tmp = find_value("PATH", g_env);
	paths = ft_split(tmp, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin("/", inst);
		new_path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (stat(new_path, &s) == 0)
			return (new_path);
		free(new_path);
		i++;
	}
	return (ft_strdup(inst));
}

void get_status()
{
	static int status;

	status = 0;
	return (&status);
}

