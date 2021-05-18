#include "ft_env_lst.h"

t_env	*ft_envinit(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == 0)
		return (0);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = 0;
	return (env);
}

void	set_genv(t_env *root, char **envp)
{
	char	**chunk;
	char	**curr;
	int		cnt_args;

	curr = envp;
	while (*curr)
	{
		chunk = ft_split(*curr, '=');
		cnt_args = ft_cnt_lines(*curr, '=');
		if (cnt_args == 2)
			ft_envadd_back(&root, ft_envinit(chunk[0], chunk[1]));
		else
			ft_envadd_back(&root, ft_envinit(chunk[0], ""));
		ft_free_chunks(chunk, cnt_args);
		curr++;
	}
}

void	free_genv(t_env *env)
{
	t_env	*del;
	t_env	*curr;

	curr = env;
	del = curr;
	while (del != 0)
	{
		curr = del->next;
		ft_envfree(del);
		del = curr;
	}
}

void	ft_envprint_all(t_env *root)
{
	t_env	*curr;

	curr = root;
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}
