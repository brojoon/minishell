#include "minishell.h"

int	cnt_quotes(char *str, char c, int *meta_arr)
{
	int	st;
	int	cnt;

	st = 0;
	cnt = 0;
	if (!str)
		return (cnt);
	while (str[st])
	{
		if (str[st] == c && meta_arr[st] == 1)
			cnt++;
		st++;
	}
	return (cnt);
}

/*
 * quotes로 str을 감싸는 함수
*/
char	*encap_quotes(char *str, char quote)
{
	char	*ret;

	ret = 0;
	ft_resize_and_copy(&ret, &quote, 0, 1);
	ft_resize_and_copy(&ret, str, 0, 2);
	ft_resize_and_copy(&ret, &quote, 0, 1);
	return (ret);
}

/*
 * quotes로 감싸진 str의 내용물만 return
*/
char	*decap_quotes(char *str, char *quote)
{
	char	*ret;

	ret = ft_substr(str, 1, ft_strlen(str) - 2);
	*quote = str[0];
	return (ret);
}

int	get_meta_arr_sub(char *str, int st, int *ret)
{
	if (str[st] == '\'')
	{
		if (st == 0 || !(str[st - 1] == '\\' && ret[st - 1] == 1))
		{
			ret[st++] = 1;
			while (str[st] && str[st] != '\'')
				ret[st++] = 0;
			ret[st] = 1;
		}
		else
			ret[st] = 0;
	}
	else if (st > 0 && str[st - 1] == '\\' && ret[st - 1] == 1)
		ret[st] = 0;
	else if (str[st] == '\\' || str[st] == '\''
		|| str[st] == '\"' || str[st] == '$')
		ret[st] = 1;
	else
		ret[st] = 0;
	return (0);
}

/*
 * 일반 문자, / 뒤에 있는 $, ", `는 meta x(0)
 * 그 외에는 meta (1)
*/
int	*get_meta_arr(char *str)
{
	int	*ret;
	int	st;

	ret = (int *)malloc(sizeof(int) * ft_strlen(str));
	st = 0;
	while (str[st])
	{
		get_meta_arr_sub(str, st, ret);
		st++;
	}
	return (ret);
}
