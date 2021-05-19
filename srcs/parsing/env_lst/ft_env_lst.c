#include "minishell.h"

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

void	set_genv(t_env **root, char **envp)
{
	char	**chunk;
	char	**curr;
	int		cnt_args;
	t_env	*temp;

	curr = envp;
	while (*curr)
	{
		chunk = ft_split(*curr, '=');
		cnt_args = ft_cnt_lines(*curr, '=');
		if (cnt_args == 2)
			temp = ft_envinit(chunk[0], chunk[1]);
		else
			temp = ft_envinit(chunk[0], "");
		ft_envadd_back(root, temp);
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
