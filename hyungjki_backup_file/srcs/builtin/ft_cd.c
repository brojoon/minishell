#include "minishell.h"

void	alter_pwd(t_env *envs)
{
	t_env	*pwd;
	char	dir[1024];

	pwd = get_env(envs, "PWD");
	getcwd(dir, 1024);
	edit_env_value(envs, "OLDPWD", ft_strdup(pwd->value));
	edit_env_value(envs, "PWD", ft_strdup(dir));
}

void	ft_cd(t_inst *inst, t_env *envs)
{
	t_string	*arg;

	arg = inst->arg;
	g_status = 0;
	if (arg == NULL || arg->str == NULL)
		return ;
	if (chdir(arg->str) == -1)
	{
		error_msg_join("cd: ", arg->str, strerror(errno));
		errno = 1;
		g_status = 1;
		return ;
	}
	alter_pwd(envs);
}
