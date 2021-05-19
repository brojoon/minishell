#include "minishell.h"

void	alter_pwd(t_env *envs)
{
	t_env	*pwd;
	char	dir[1024];

	pwd = get_env(envs, "PWD");
	getcwd(dir, 1024);
	edit_env_value(envs, "OLDPWD", ft_strdup(pwd->value));
	edit_env_value(envs, "PWD", ft_strdup(dir));
	g_status = 0;
}

void	cd_error_handle(char *str1, char *str2)
{
	error_msg_join("cd: ", str1, str2);
	g_status = 1;
	return ;
}

void	ft_cd(t_inst *proc, t_env *envs)
{
	printf("here3");
	if (proc->arg == NULL || proc->arg->str == NULL)
	{
		while (envs && envs->next && ft_strcmp(envs->key, "HOME"))
			envs = envs->next;
		if (!ft_strcmp(envs->key, "HOME"))
		{
			if (chdir(envs->value) == -1)
				cd_error_handle(envs->value, ": No such file or directory");
			else
				alter_pwd(envs);
			return ;
		}
		else
			catch_error("cd", "HOME not set");
		g_status = 1;
		return ;
	}
	else if (chdir(proc->arg->str) == -1)
		cd_error_handle(proc->arg->str, ": No such file or directory");
	else
		alter_pwd(envs);
}
