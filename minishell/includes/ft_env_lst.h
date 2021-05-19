#ifndef FT_ENV_LST_H
# define FT_ENV_LST_H
# include "get_next_line.h"
typedef struct s_env	t_env;
struct					s_env
{
	char				*key;
	char				*value;
	t_env				*next;
};

/*
** ft_env_lst.c
*/
t_env	*ft_envinit(char *key, char *value);
void	set_genv(t_env *root, char **envp);
void	free_genv(t_env *env);
void	ft_envprint_all(t_env *root);
/*
** ft_env_lst_utils.c
*/
t_env	*ft_envfind(t_env *env, char *key);
void	ft_envfree(t_env *env);
void	ft_envremove(t_env **root, char *key);
void	ft_envadd_back(t_env **root, t_env *now);
void	ft_envchkandadd(t_env **root, t_env *now, int flag);
#endif
