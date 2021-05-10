#include "../minishell.h"

static void alter_pwd(t_env *g_env)
{
	t_env *pwd;
	char dir[1024];

	pwd = get_env(g_env, "PWD");
	getcwd(dir, 1024);
	edit_env_value(g_env, "OLDPWD", ft_strdup(pwd->value));
	edit_env_value(g_env, "PWD", ft_strdup(dir));
}

void ft_cd(t_inst *inst, t_env *g_env)
{
	t_string *arg;

	arg = inst->arg;
	if (arg == NULL || arg->str == NULL)
		return ;
	if (chdir(arg->str) == -1)
	{
		error_msg_join("cd: ", arg->str, errno);
		errno = 1;
		return ;
	}
	alter_pwd(g_env);
}