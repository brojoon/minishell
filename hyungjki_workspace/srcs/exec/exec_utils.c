#include "../../includes/minishell.h"

char *find_value(char *key, t_env *g_env)
{
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

char **envs_to_chunks(t_env *g_env)
{
	int size;
	t_env *list;
	char **chunks;
	char *tmp;
	list = g_env;
	size = 0;
	while (list)
	{
		list = list->next;
		size++;
	}
	chunks = (char **)malloc(sizeof(t_env) * size + 1);
	size = 0;
	while(g_env)
	{
		tmp = ft_strjoin(g_env->key, g_env->value);
		chunks[size] = tmp;
		size++;
		g_env = g_env->next;
	}
	chunks[size] = NULL;
	return (chunks);
}

int *get_status()
{
	static int status;

	status = 0;
	return (&status);
}

