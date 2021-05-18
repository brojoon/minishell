#include "minishell.h"

char	*find_value(char *key, t_env *envs)
{
	while (envs)
	{
		if (!ft_strcmp_j(envs->key, key))
			return (envs->value);
		envs = envs->next;
	}
	return (0);
}

char	*get_path(char *inst, t_env *envs)
{
	int			i;
	char		*tmp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	tmp = find_value("PATH", envs);
	paths = ft_split_j(tmp, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin_j("/", inst);
		new_path = ft_strjoin_j(paths[i], tmp);
		free(tmp);
		if (stat(new_path, &s) == 0)
			return (new_path);
		free(new_path);
		i++;
	}
	return (ft_strdup_j(inst));
}

char	**envs_to_chunks(t_env *envs)
{
	int		size;
	char	**chunks;
	char	*tmp;
	char	*tmp2;

	size = get_envs_size(envs);
	chunks = (char **)malloc(sizeof(t_env) * size + 1);
	size = 0;
	while (envs)
	{
		tmp = ft_strjoin_j(envs->key, "=");
		tmp2 = ft_strjoin_j(tmp, envs->value);
		chunks[size] = tmp2;
		free(tmp);
		size++;
		envs = envs->next;
	}
	chunks[size] = NULL;
	return (chunks);
}

void	print_status(void)
{
	char	*str;

	str = ft_itoa_j(g_status);
	ft_putstr_fd_j(str, STDERR_FILENO);
	ft_putendl_fd_j(": command not found", STDERR_FILENO);
	free(str);
	g_status = 127;
}
