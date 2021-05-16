#include "main.h"

/*
 * 인자가 2개 이상이거나 없는 경우 error
*/
int ft_cd(t_env *env, t_inst *inst)
{
	t_string *arg;
	t_env *temp_env;
	char buf[BUFFER_SIZE];

	arg = inst->arg;
	if (arg == 0)
		return (1);
	else if (ft_lstcount(arg) != 1)
		return (1);
	if (chdir(arg->str) == -1)
		return (1);
	temp_env = ft_envfind(env, "PWD");
	if (temp_env)
	{
		free(temp_env->value);
		temp_env->value = ft_strdup(getcwd(buf, 1024));
	}
	return (0);
}

int ft_pwd(void)
{
	char buf[BUFFER_SIZE];
	char *buf_ptr;
	if ((buf_ptr = getcwd(buf, 1024)) == 0)
		return (1);
	else
		printf("%s\n", buf_ptr);
	return (0);
}

/*
 * 추후 개발 
*/

int ft_echo(t_inst *inst)
{
	t_string *arg;

	arg = inst->arg;
	if (arg == 0 || arg->str == 0)
		printf("\n");
	else
	{
		write(1, arg->str, ft_strlen(arg->str));
		if (inst->option == 0 || ft_strncmp(inst->option, "-n", 2) != 0)
			write(1, "\n", 1);
	}
	return (0);
}

/*
 * variable name은 a to z, A to Z, 0 to 9, _만 가능
 * 숫자로만 구성된 variable name은 불가
*/
int ft_chk_key(char *s)
{
	int st;
	int alpha_flag;
	char c;

	st = 0;
	alpha_flag = 1;
	if (s == 0)
		return (0);
	while ((c = s[st]) != 0)
	{
		if (c < '0')
			return (1);
		if (c > '9' && c != '_')
		{
			if (c < 'A' || (c > 'Z' && c < 'a') || (c > 'z'))
				return (1);
			else
				alpha_flag = 0;
		}
		st++;
	}
	if (alpha_flag == 1)
		return (1);
	return (0);
}
/*
int ft_chk_export(t_inst *inst)
{
	t_string *arg;
	char **chunk;

	arg = inst->arg;
	while (arg != 0)
	{
		printf("arg:%s\n", arg->str);
		if (ft_strncmp(arg->str, "=", 1) == 0)
			;
		else
		{
			chunk = ft_split(arg->str, '=');
			printf("chunk:%s\n", chunk[0]);
			if (ft_chk_key(chunk[0])){
				ft_free_chunks(chunk, ft_cnt_lines(arg->str, '='));
				return (1);
			}
			ft_free_chunks(chunk, ft_cnt_lines(arg->str, '='));
		}
		arg = arg->next;
	}
	return (0);
}
*/

/*
 * export, export a, export a=, export =a, export =, export a+=3, export +=3, export a+=;
 * declare -ax (array) 는 처리하지 않음
 * 0 : 정상
 * 1 : 유효한 식별자가 아님
*/
int ft_export(t_env *env, t_inst *inst)
{
	t_string *arg;
	char ** chunk;
	int ret;
	int append_flag;

	arg = inst->arg;
	ret = 0;
	// export 출력
	if (arg == 0 || arg->str == 0)
	{
		return (ret);
	}
	while (arg)
	{
		append_flag = 0;
		if ((ft_strchr(arg->str, '=') == 0) && ft_chk_key(arg->str) != 0)
			ret = 1;
		else if ((ft_strchr(arg->str, '=') != 0) && 
					((ft_strncmp(arg->str, "=", 1) == 0)
					|| (ft_strncmp(arg->str, "+=", 2) == 0)))
			ret = 1;
		else if (ft_strchr(arg->str, '=') != 0)
		{
			chunk = ft_split(arg->str, '=');
			if (ft_strnstr(arg->str, "+=", ft_strlen(arg->str)) != 0)
			{
				append_flag = 1;
				chunk[0] = ft_substr(chunk[0], 0, ft_strlen(chunk[0]) - 1);
			}
			if (ft_chk_key(chunk[0]) == 0)
			{
				if (ft_cnt_lines(arg->str, '=') == 1)
					ft_envchkandadd(&env, ft_envinit(chunk[0], ""), append_flag);
				else
					ft_envchkandadd(&env, ft_envinit(chunk[0], chunk[1]), append_flag);
			}
			else
				ret = 1;
			ft_free_chunks(chunk, ft_cnt_lines(arg->str, '='));
		}
		arg = arg->next;
	}
	return (ret);
}

int ft_env(t_env *env, t_inst *inst)
{
	ft_envprint_all(env);
	return (0);
}

int ft_unset(t_env *env, t_inst *inst)
{
	t_string *arg;

	arg = inst->arg;
	while (arg)
	{
		ft_envremove(&env, arg->str);
		arg = arg->next;
	}
	return (0);
}
/* 추후 삭제 예정 */
int ft_ls(t_inst *inst)
{
	t_string *arg;
	DIR *dir_ptr;
	struct dirent *file;
	int cnt;

	if (inst->arg == 0)
		inst->arg = ft_lstinit(ft_strdup("."));
	arg = inst->arg;
	cnt = 0;
	while (arg)
	{
		printf("%s:\n", arg->str);
		if ((dir_ptr = opendir(arg->str)) == 0)
			return (1);
		while ((file = readdir(dir_ptr)) != 0)
			printf("%s\n", file->d_name);
		if (cnt > 0)
			printf("\n");
		closedir(dir_ptr);
		arg = arg->next;
		cnt++;
	}
	return (0);
}
