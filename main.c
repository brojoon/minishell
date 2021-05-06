#include "main.h"

int get_next_line(int fd, char **line, char *prompt);

/*
 * 프롬프트는 cwd를 가져와서 출력하는 것으로 하였습니다.
 * 추후 cd 명령어로 이동할 때마다 prompt를 변경해주면 될 것 같아요.
*/
char *get_prompt(){
	char	buf[BUFFER_SIZE];
	char	*buf_ptr;
	char	*prompt;

	buf_ptr = getcwd(buf, 1024);
	prompt = ft_strdup(buf_ptr);
	ft_resize_and_copy(&prompt, " % ", 0, 3);
	return prompt;
}

char	*ft_strchr(char *s, int c)
{
	int	st;

	st = 0;
	while (*(s + st))
	{
		if (*(s + st) == (char)c)
			return ((char *)(s + st));
		st++;
	}
	if (c == '\0')
		return ((char *)(s + st));
	return (0);
}

char	*ft_strrchr(char *s, int c)
{
	int	st;
	char *ret;

	st = 0;
	ret = 0;
	while (*(s + st))
	{
		if (*(s + st) == (char)c)
			ret = (char *)(s + st);
		st++;
	}
	if (c == '\0')
		ret = (char *)(s + ft_strlen(s));
	return (ret);
}

int		ft_cnt_lines(char *s, char c)
{
	int	st;
	int	cnt;

	st = 0;
	cnt = 0;
	while (s[st] && s[st] == c)
		st++;
	while (s[st])
	{
		st = ft_get_next_idx(s, c, st);
		cnt++;
		while (s[st] && s[st] == c)
			st++;
	}
	return (cnt);
}

void	ft_free_chunks(char **ret, int ret_st)
{
	int	st;

	st = 0;
	if (*ret == 0)
		return ;
	while (st < ret_st)
		free(*(ret + (st++)));
	free(ret);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*ret;
	int	ed;
	int	st;

	if (!s)
		return (0);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	st = 0;
	if (ft_strlen(s) >= start)
	{
		ed = start + len;
		while (start < ed)
			ret[st++] = s[start++];
	}
	ret[st] = '\0';
	return (ret);
}

char	**ft_split(char *s, char c)
{
	char	**ret;
	int		ret_st;
	int		st;

	if (!s)
		return (0);
	if (!(ret = (char **)malloc(sizeof(char *) * (ft_cnt_lines(s, c) + 1))))
		return (0);
	ret_st = 0;
	st = 0;
	while (s[st] && s[st] == c)
		st++;
	while (s[st] && ret_st < ft_cnt_lines(s, c))
	{
		if (!(ret[ret_st++] = ft_substr(s, st, ft_get_next_idx(s, c, st) - st)))
		{
			ft_free_chunks(ret, ret_st);
			return (0);
		}
		st = ft_get_next_idx(s, c, st);
		while (s[st] && s[st] == c)
			st++;
	}
	ret[ret_st] = 0;
	return (ret);
}

int cnt_quotes(char *str, char c, int *meta_arr)
{
	int st;
	int cnt;

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
 * 일반 문자, / 뒤에 있는 $, ", `는 meta x(0)
 * 그 외에는 meta (1)
*/
int *get_meta_arr(char *str)
{
	int *ret;
	int st;

	ret = (int *)malloc(sizeof(int) * ft_strlen(str));
	st = 0;
	while (str[st])
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
		else if (str[st] == '\\' || str[st] == '\'' || str[st] == '\"' || str[st] == '$')
			ret[st] = 1;
		else
			ret[st] = 0;
		st++;
	}
	return (ret);
}

int quotes_sub_loop(char **buf, int **meta_arr, char target)
{
	char *temp;

	// 짝이 맞지 않는 경우
	while (cnt_quotes(*buf, target, *meta_arr) % 2 == 1)
	{
		get_next_line(0, &temp, "> ");
		ft_resize_and_copy(buf, "\n", 0, 1);
		ft_resize_and_copy(buf, temp, 0, ft_strlen(temp));
		free(temp);
		free(*meta_arr);
		*meta_arr = get_meta_arr(*buf);
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int len)
{
	int	st;

	st = 0;
	while (s1[st] && s2[st] && st < len)
	{
		if (s1[st] != s2[st])
			return ((unsigned char)s1[st] - (unsigned char)s2[st]);
		st++;
	}
	if (len <= 0 || st == len)
		return (0);
	return ((unsigned char)s1[st] - (unsigned char)s2[st]);
}

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	st;
	size_t	lt_len;

	st = 0;
	lt_len = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	else if (!big)
		if (big[st])
			st = 0;
	while (st + lt_len <= len)
	{
		while (big[st] && big[st] != little[0])
			st++;
		if (!big[st] || st + lt_len > len)
			break ;
		if (!ft_strncmp(&big[st], little, lt_len))
			return (&((char *)big)[st]);
		st++;
	}
	return (0);
}

t_string *ft_lstfind(t_string *root, char *target)
{
	t_string *curr;

	curr = root;
	while (curr)
	{
		if (ft_strnstr(curr->str, target, ft_strlen(curr->str)) != 0)
			return (curr);
		curr = curr->next;
	}
	return (0);
}

void ft_lstfree(t_string *del)
{
	free(del->str);
	free(del);
	del = 0;
}

int ft_lstcount(t_string *arg)
{
	t_string *curr;
	int cnt;

	cnt = 0;
	if (arg == 0)
		return (cnt);
	else
	{
		curr = arg;
		while (curr)
		{
			curr = curr->next;
			cnt++;
		}
	}
	return (cnt);
}

t_string *ft_lstremove(t_string **root, t_string *target)
{
	t_string *curr;
	t_string *prev;
	t_string *del;

	del = target;
	curr = *root;
	prev = 0;
	while (curr && ft_strncmp(curr->str, target->str, ft_strlen(curr->str)) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == 0)
		*root = curr->next;
	else
		prev->next = curr->next;
	ft_lstfree(del);
	if (prev == 0)
		return (*root);
	return (prev->next);
}

void ft_lstfree_all(t_string *root)
{
	t_string *del;

	del = root;
	while (del)
	{
		root = del->next;
		ft_lstfree(del);
		del = root;
	}
}

void ft_inst_free(t_inst *root)
{
	t_inst *del;

	del = root;
	while (del)
	{
		root = del->next;
		free(del->inst);
		free(del->option);
		ft_lstfree_all(del->rd);
		ft_lstfree_all(del->arg);
		ft_inst_free(del->child);
		free(del);
		del = root;
	}
}

int ft_lst_get_len(t_string *root)
{
	t_string *curr;
	int cnt;

	curr = root->next;
	cnt = 0;
	while (curr)
	{
		cnt++;
		curr = curr->next;
	}
	return (cnt);
}

t_string *ft_lstinit(char *s)
{
	t_string *temp;

	if (!(temp = (t_string *)malloc(sizeof(t_string))))
		return (0);
	temp->str = s;
	temp->next = 0;
	return (temp);
}

void ft_lstadd_front(t_string **root, t_string *s)
{
	t_string *curr;

	if (*root == 0)
		*root = s;
	else
	{
		curr = s;
		while (curr->next)
			curr = curr->next;
		curr->next = *root;
		*root = s;
	}
}

void ft_lstadd_after(t_string **root, t_string *s)
{
	if (*root == 0)
		*root = s;
	else
	{
		s->next = (*root)->next;
		(*root)->next = s;
	}
}

void ft_lstadd_back(t_string **root, t_string *s)
{
	t_string *curr;

	if (*root == 0)
		*root = s;
	else
	{
		curr = *root;
		while (curr->next != 0)
			curr = curr->next;
		curr->next = s;
	}
}
/*
 * ;(semi-colon)으로 나뉜 애들은 sibling
*/
void ft_instadd_sibling(t_inst **root, t_inst *inst)
{
	t_inst *curr;

	if (*root == 0)
		*root = inst;
	else
	{
		curr = *root;
		while (curr->next != 0)
			curr = curr->next;
		curr->next = inst;
	}
}

/*
 * |(pipe)로 나뉜 애들은 child
*/
void ft_instadd_child(t_inst **root, t_inst *inst)
{
	t_inst *curr;

	if (*root == 0)
		*root = inst;
	else
	{
		curr = *root;
		while (curr->child != 0)
			curr = curr->child;
		curr->child = inst;
	}
}

/*
 * buf의 st ~ ed를 char *to로 치환하는 함수
*/
char *replace_str(char **buf, int st, int ed, char *to)
{
	char *temp;
	char *now_str;

	temp = 0;
	if (st == ed - 1)
		return (0);
	now_str = ft_substr(*buf, st, ed - st + 1);
	ft_resize_and_copy(&temp, *buf, 0, st);
	ft_resize_and_copy(&temp, to, 0, ft_strlen(to));
	ft_resize_and_copy(&temp, *buf, ed + 1, ft_strlen(*buf));
	free(*buf);
	*buf = temp;
	return (now_str);
}

t_inst *ft_instinit()
{
	t_inst *ret;

	if (!(ret = (t_inst *)malloc(sizeof(t_inst))))
		return (0);
	ret->inst = 0;
	ret->option = 0;
	ret->rd = 0;
	ret->arg = 0;
	ret->next = 0;
	ret->child = 0;
	return (ret);
}

/*
 * 명령어 및 인자에 redireciton이 있는지 확인
 * redirection은 splitter에 넣어주고 splitter로 자른 char **를 return
*/
char **split_redirection(char *str, char **splitter)
{
	char **ret;

	if (splitter == 0)
		*splitter = 0;
	if (ft_strchr(str, '>') != 0)
	{
		ret = ft_split(str, '>');
		if (ft_strnstr(str, ">>", ft_strlen(str)) != 0)
			*splitter = ">>";
		else
			*splitter = ">";
	}
	else if (ft_strchr(str, '<') != 0)
	{
		ret = ft_split(str, '<');
		*splitter = "<";
	}
	else
		ret = 0;
	return (ret);
}

/*
 * 한번에 2개 이상의 redirection이 붙어있는 경우 error
*/
int check_red_error(char *inst)
{
	int num_of_lines;
	int num_of_lines2;

	num_of_lines = ft_cnt_lines(inst, '>');
	num_of_lines2 = ft_cnt_lines(inst, '<');
	if (num_of_lines > 2 || num_of_lines2 > 2)
		return (1);
	if (ft_strchr(inst, '<') && ft_strchr(inst, '>'))
		return (1);
	return (0);
}

int	ft_make_int(const char *ptr, int st, int ed, int sign)
{
	unsigned long	ret;
	unsigned long	mod;

	ret = 0;
	mod = 1;
	while (--ed >= st)
	{
		ret += ((unsigned long)(ptr[ed] - '0') * mod);
		mod *= 10;
	}
	if (ret > 2147483647 && sign == 1)
		return (-1);
	else if (ret > 2147483648 && sign == -1)
		return (0);
	return (ret * sign);
}

int	ft_atoi(const char *nptr)
{
	int		st;
	int		ed;
	int		sign;

	sign = 1;
	st = 0;
	while (nptr[st] && (nptr[st] == ' ' ||
				(nptr[st] >= 0x09 && nptr[st] <= 0x0D)))
		st++;
	if (!nptr[st])
		return (0);
	if (nptr[st] == '-')
		sign = -1;
	if (sign == -1 || nptr[st] == '+')
		st++;
	if (nptr[st] < '0' || nptr[st] > '9')
		return (0);
	ed = st;
	while (nptr[ed] >= '0' && nptr[ed] <= '9')
		ed++;
	return (ft_make_int(nptr, st, ed, sign));
}

/*
 * ret 0 : 정상 fd (0 ~ 2)
 * ret 1 : not fd (inst or argument)
 * ret 2 : 3 ~ 9 사이의 fd
*/
int is_fd(char *s)
{
	if (ft_strlen(s) > 1)
		return (1);
	if (*s < '0' || *s > '9')
		return (1);
	else if (*s > '2' && *s <= '9')
		return (2);
	return (0);
}

/*
 * space 단위로 쪼개진 chunk에서 '<', '>', '>>' catch
 * redirection으로 쪼갰을 때 2개가 나오면 왼쪽은 fd 혹은 명령어/인자
 * ret 0 : 정상
 * ret 1 : fd가 잘못된 경우
 * ret 2 : redirection 오류
 * ret 3 : parse error
*/
int handle_red_token(t_inst *inst, char **cmd, int *k)
{
	char *red;
	char **chunks;
	char *now;

	now = *(cmd + *k);
	red = 0;
	if (check_red_error(now) != 0)
		return (2);
	chunks = split_redirection(now, &red);
	if (red != 0)
	{
		if (ft_cnt_lines(now, red[0]) == 2)
		{
			if (is_fd(chunks[0]) == 0)
			{
				if (chunks[0][0] == '2' && red[0] == '>')
					chunks[0][0] = '0';
				if (chunks[0][0] == '1' && red[0] == '>')
					;
				else if (chunks[0][0] == '0' && red[0] == '<')
					;
				else
					ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(chunks[0])));
			}
			else if (is_fd(chunks[0]) == 1)
			{
				if (inst->inst == 0)
					inst->inst = ft_strdup(chunks[0]);
				else
					ft_lstadd_back(&(inst->arg), ft_lstinit(ft_strdup(chunks[0])));
			}
			else
			{
				ft_free_chunks(chunks, ft_cnt_lines(now, red[0]));
				return (1);
			}
			ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(red)));
			ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(chunks[1])));
		}
		else if (ft_cnt_lines(now, red[0]) == 1)
		{
			ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(chunks[0])));
			if (ft_strncmp(now, red, ft_strlen(red)) == 0)
				ft_lstadd_front(&(inst->rd), ft_lstinit(ft_strdup(red)));
			else
			{
				ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(red)));
				if (*(cmd + *k + 1) == 0)
				{
					ft_free_chunks(chunks, ft_cnt_lines(now, red[0]));
					return (3);
				}
				ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(*(cmd + ++(*k)))));
				}
		}
		else
		{
			if (*(cmd + *k + 1) == 0)
			{
				ft_free_chunks(chunks, ft_cnt_lines(now, red[0]));
				return (3);
			}
			ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(red)));
			ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(*(cmd + ++(*k)))));
		}
		ft_free_chunks(chunks, ft_cnt_lines(now, red[0]));
	}
	else
		return (-1);
	return (0);
}

/*
 * redirection은 어느 위치든 나올 수 있음
 * -로 시작하면 option으로 인식(인자 뒤에 나올 경우 인자로 인식)
 * -로 시작하는 option이 여러개인 경우 첫 번째만 인식
*/
t_inst *make_command(char **space_chunks, int line_cnt)
{
	int k;
	t_inst *ret;
	t_string *arg;
	int flag;

	ret = ft_instinit();
	k = 0;
	while (*(space_chunks + k))
	{
		flag = handle_red_token(ret, space_chunks, &k);
		if (flag > 0)
		{
			printf("make_commmand err:%d\n", flag);
			ft_inst_free(ret);
			return (0);
		}
		else if (flag == -1)
		{
			if (ret->inst == 0)
				ret->inst = ft_strdup(*(space_chunks + k));
			else if (ft_strncmp(*(space_chunks + k), "-", 1) == 0)
			{
				if (ret->arg == 0 && ret->option == 0)
					ret->option = ft_strdup(*(space_chunks + k));
				else if (ret->arg != 0)
				{
					arg = ft_lstinit(ft_strdup(*(space_chunks + k)));
					ft_lstadd_back(&ret->arg, arg);
				}
			}
			else
			{
				arg = ft_lstinit(ft_strdup(*(space_chunks + k)));
				if (ft_strncmp(arg->str, "\"\"", ft_strlen(arg->str)) == 0)
					ft_lstfree(arg);
				else if (ft_strncmp(arg->str, "\'\'", ft_strlen(arg->str)) == 0)
					ft_lstfree(arg);
				else
					ft_lstadd_back(&ret->arg, arg);
			}
		}
		k++;
	}
	ft_free_chunks(space_chunks, line_cnt);
	return (ret);
}

/*
 * echo인 경우 arg를 모두 합침
 * arg + ' ' + arg 형식
*/
void echo_merge_args(t_inst **inst)
{
	t_string *arg;
	char *temp;

	temp = 0;
	arg = (*inst)->arg;
	if (arg == 0)
		return ;
	while (arg)
	{
		ft_resize_and_copy(&temp, arg->str, 0, ft_strlen(arg->str));
		if (arg->next)
			ft_resize_and_copy(&temp, " ", 0, 1);
		arg = arg->next;
	}
	ft_lstfree_all((*inst)->arg);
	(*inst)->arg = ft_lstinit(temp);
}

/*
 * 여러 줄으로 입력받은 명령어 문자열을 |, ; 단위로 split 후 make_command 함수 호출
 * ;(semi colon)은 inst->next, |(pipe)는 inst->child로 attach
*/
t_inst *split_commands(char **semi_chunks, int line_cnt)
{
	int i;
	int j;
	char **pipe_chunks;
	t_inst *inst;
	t_inst *root;
	t_inst *temp;

	root = 0;
	if (semi_chunks == 0)
		return (0);
	i = 0;
	while (*(semi_chunks + i))
	{
		pipe_chunks = ft_split(*(semi_chunks + i), '|');
		j = 0;
		temp = 0;
		while (*(pipe_chunks + j))
		{
			inst = make_command(ft_split(*(pipe_chunks + j), ' '), ft_cnt_lines(*(pipe_chunks + j), ' '));
			if (inst == 0)
				printf("err 발생..\n");
			else
			{
				if (ft_strncmp(inst->inst, "echo", ft_strlen(inst->inst)) == 0)
					echo_merge_args(&inst);
				ft_instadd_child(&temp, inst);
			}
			j++;
		}
		ft_free_chunks(pipe_chunks, ft_cnt_lines(*(semi_chunks + i), '|'));
		ft_instadd_sibling(&root, temp);
		i++;
	}
	ft_free_chunks(semi_chunks, line_cnt);
	return (root);
}

/*
 * quotes로 str을 감싸는 함수
*/
char *encap_quotes(char *str, char quote)
{
	char *ret;

	ret = 0;
	ft_resize_and_copy(&ret, &quote, 0, 1);
	ft_resize_and_copy(&ret, str, 0, 2);
	ft_resize_and_copy(&ret, &quote, 0, 1);
	return (ret);
}

/*
 * quotes로 감싸진 str의 내용물만 return
*/
char *decap_quotes(char *str, char *quote)
{
	char *ret;

	ret = ft_substr(str, 1, ft_strlen(str) - 2);
	*quote = str[0];
	return (ret);
}

/*
 * quotes(", ')사이의 string을 const_strings로 옮기고 %%로 변경
*/
void handle_quotes(char **buf, t_string **const_strings)
{
	int st;
	int ed;
	char *prev_str;
	char *rep;
	char now;
	int *meta_arr;

	meta_arr = get_meta_arr(*buf);
	st = 0;
	while ((now = *(*buf + st)))
	{
		if ((now == '\'' || now == '\"') && meta_arr[st] == 1)
		{
			quotes_sub_loop(buf, &meta_arr, now);
			rep = encap_quotes("%%", now);
			ed = ft_get_next_idx(*buf, now, st + 1);
			while (meta_arr[ed] == 0)
				ed = ft_get_next_idx(*buf, now, ed + 1);
			if ((prev_str = replace_str(buf, st, ed, rep)) != 0)
			{
				ft_lstadd_back(const_strings, ft_lstinit(ft_strdup(prev_str)));
				free(meta_arr);
				meta_arr = get_meta_arr(*buf);
			}
			free(rep);
			st = ft_get_next_idx(*buf, now, st + 1);
		}
		st++;
	}
	free(meta_arr);
}

/*
 * execve에 넣기 위한 t_string *의 형식 변경 함수
*/
char **inst_to_chunks(t_inst *inst)
{
	char **ret;
	t_string *curr;
	int st;

	if ((ret = (char **)malloc(sizeof(char *) * (ft_lstcount(inst->rd)+ft_lstcount(inst->arg) + 3))) == 0)
		return (0);
	*ret = inst->inst;
	*(ret + 1) = inst->option;
	curr = inst->rd;
	st = 2;
	while (curr)
	{
		*(ret + (st++)) = curr->str;
		curr = curr->next;
	}
	curr = inst->arg;
	while (curr)
	{
		*(ret + (st++)) = curr->str;
		curr = curr->next;
	}
	*(ret + st) = 0;
	return (ret);
}

t_env *ft_envinit(char *key, char *value)
{
	t_env *env;

	if ((env = (t_env *)malloc(sizeof(t_env))) == 0)
		return (0);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = 0;
	return (env);
}

t_env *ft_envfind(char *key)
{
	t_env *curr;

	curr = g_env;
	if (curr == 0)
		return (0);
	while (curr && ft_strncmp(curr->key, key, ft_strlen(curr->key)) != 0)
	{
		curr = curr->next;
	}
	return (curr);
}

void ft_envfree(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void ft_envremove(t_env **root, char *key)
{
	t_env *curr;
	t_env *prev;
	t_env *del;
	
	curr = *root;
	prev = 0;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(curr->key)) == 0)
		{
			if (prev == 0)
				*root = curr->next;
			else
			{
				del = curr;
				prev->next = curr->next;
				ft_envfree(del);
			}
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void ft_envadd_back(t_env **root, t_env *now)
{
	t_env *curr;

	if (*root == 0)
		*root = now;
	else
	{
		curr = *root;
		while (curr->next)
			curr = curr->next;
		curr->next = now;
	}
}

/*
 * flag : append 여부 (0 : remove and add, 1 : append)
*/
void ft_envchkandadd(t_env **root, t_env *now, int flag)
{
	t_env *curr;

	curr = ft_envfind(now->key);
	if (curr == 0)
		ft_envadd_back(root, now);
	else
	{
		if (flag == 1)
			ft_resize_and_copy(&curr->value, now->value, 0, ft_strlen(now->value));
		else
		{
			free(curr->value);
			curr->value = ft_strdup(now->value);
		}
		ft_envfree(now);
	}
}

void ft_envprint_all(t_env *root)
{
	t_env *curr;

	curr = root;
	while (curr)
	{
		printf("%s=%s\n",curr->key, curr->value);
		curr = curr->next;
	}
}
void set_genv(char **envp)
{
	char **chunk;
	char **curr;
	int cnt_args;

	curr = envp;
	while (*curr)
	{
		chunk = ft_split(*curr, '=');
		cnt_args = ft_cnt_lines(*curr, '=');
		if (cnt_args == 2)
			ft_envadd_back(&g_env, ft_envinit(chunk[0], chunk[1]));
		else
			ft_envadd_back(&g_env, ft_envinit(chunk[0], ""));
		ft_free_chunks(chunk, cnt_args);
		curr++;
	}
}

void free_genv()
{
	t_env *del;
	t_env *curr;

	curr = g_env;
	while ((del = curr) != 0)
	{
		curr = del->next;
		ft_envfree(del);
	}
}

/*
 * meta char 처리 함수
*/
char *proc_metachar(char *s)
{
	int st;
	int ed;
	char *ret;
	t_env *env;
	int *meta_arr;

	st = 0;
	ret = 0;
	meta_arr = get_meta_arr(s);
	while (s[st])
	{
		if (s[st] == '\\' && meta_arr[st] == 1 && s[st + 1] != 0)
		{
			st++;
			if (s[st] != '$' && s[st] != '`' && s[st] !='"' && s[st] != '\\')
			{
				meta_arr[--st] = 0;
				continue ;
			}
			if (s[st] == '$')
			{
				ed = st + 1;
				while (s[ed] && ((s[ed] >= 'A' && s[ed] <= 'Z' ) ||
							(s[ed] >= '0' && s[ed] <= '9')))
				ed++;
			}
			ed = st;
			ft_resize_and_copy(&ret, s, st, ed);
			st = ed - 1;

		}
		else if (s[st] == '$' && meta_arr[st] == 1)
		{
			ed = st + 1;
			while (s[ed] && ((s[ed] >= 'A' && s[ed] <= 'Z') ||
						(s[ed] >= '0' && s[ed] <= '9')))
				ed++;
			env = ft_envfind(ft_substr(s, st + 1, ed));
			if (env != 0)
				ft_resize_and_copy(&ret, env->value, 0, ft_strlen(env->value));
			st = ed - 1;
		}
		else
			ft_resize_and_copy(&ret, &s[st], 0, 1);
		if (s[st] == 0)
			break ;
		st++;
	}
	free(meta_arr);
	return (ret);
}

/*
 * Quotes(", ')에 묶인 문자열 처리 함수
 * single quotes인 경우 그냥 내용물 출력
 * double quotes인 경우 $, \ 처리
*/
void proc_quotes(char **now)
{
	char *decap_str;
	char *new_str;
	char quote;
	
	if (*now == 0)
		return ;
	decap_str = decap_quotes(*now, &quote);
	if (quote == '\"')
		new_str = proc_metachar(decap_str);
	else
		new_str = ft_strdup(decap_str);
	free(*now);
	*now = new_str;
}

/*
 * const_strings에 묶인 문자열을 inst에 있는 문자열 %%와 치환
*/
void get_ori_consts(t_string *str, t_inst **inst)
{
	t_inst *curr;
	t_string *arg;
	t_string *const_now;
	char *temp;
	int st;
	int ed;

	curr = *inst;
	const_now = str;
	while (curr)
	{
		arg = curr->arg;
		while (arg)
		{
			st = 0;
			temp = 0;
			while ((arg->str)[st])
			{
				if (((arg->str)[st] == '\'' || (arg->str)[st] == '\"')
						&& (ft_strncmp(arg->str + st, encap_quotes("%%", (arg->str)[st]),
								4) == 0))
				{
					ft_resize_and_copy(&temp, const_now->str, 0, ft_strlen(const_now->str));
					st += 3;
					const_now = const_now->next;
				}
				else
					ft_resize_and_copy(&temp, arg->str, st, st + 1);
				st++;
			}
			free(arg->str);
			arg->str = temp;
			arg = arg->next;
		}
		curr = curr->child;
	}
}


void proc_consts(t_string **consts)
{
	t_string *now;
	char * now_str;
	now = *consts;
	while (now)
	{
		proc_quotes(&(now->str));
		now = now->next;
	}
}

void proc_inst_metachar(t_inst **insts)
{
	t_inst *now;
	t_inst *children;
	char *new_str;
	t_string *arg;

	now = *insts;
	while (now)
	{
		children = now;
		while (children)
		{
			new_str = proc_metachar(children->inst);
			free(children->inst);
			children->inst = new_str;
			arg = children->arg;
			while (arg != 0)
			{
				new_str = proc_metachar(arg->str);
				free(arg->str);
				arg->str = new_str;
				arg = arg->next;
			}
			children = children->child;
		}
		now = now->next;
	}
}
int main(int argc, char **argv, char **envp){
	char *buf;
	char *prompt;
	t_inst *insts;
	t_string *const_strings;

	(void)argc;
	(void)argv;
	set_genv(envp);
	prompt = get_prompt();
	while (1)
	{
		get_next_line(0, &buf, prompt);
		const_strings = 0;
		handle_quotes(&buf, &const_strings);
		insts = split_commands(ft_split(buf, ';'), ft_cnt_lines(buf, ';'));
		proc_consts(&const_strings);
		proc_inst_metachar(&insts);
		get_ori_consts(const_strings, &insts);
		free(buf);
		t_inst *curr = insts;
		/*
		while (curr != 0)
		{
			printf("-----parsing result-----\n");
			printf("inst:%s\n",curr->inst);
			printf("\toption:%s\n",curr->option);
			for (t_string *r = curr->rd; r; r = r->next)
				printf("\t\trd:%s\n",r->str);
			for (t_string *r = curr->arg; r; r = r->next)
				printf("\t\t\targ:%s\n",r->str);
			printf("-----execute result-----\n");
			// cd
			if (ft_strnstr(curr->inst, "cd", ft_strlen(curr->inst)) != 0
					&& ft_strlen(curr->inst) == 2)
			{
				if (ft_cd(curr) == 0)
				{
					free(prompt);
					prompt = get_prompt();
				}
				else
					printf("%s: 파일 이나 디렉터리 없음\n", curr->inst);

			}
			else if (ft_strnstr(curr->inst, "pwd", ft_strlen(curr->inst)) != 0
					&& ft_strlen(curr->inst) == 3)
			{
				if (ft_pwd() == -1)
					printf("error 발생\n");
			}
			else if (ft_strnstr(curr->inst, "ls", ft_strlen(curr->inst)) != 0
					&& ft_strlen(curr->inst) == 2)
			{
				if (ft_ls(curr) == 1)
				{
					printf("error 발생\n");
				}
			}
			else if (ft_strnstr(curr->inst, "exit", ft_strlen(curr->inst)) != 0
					&& ft_strlen(curr->inst) == 4)
			{
				free_genv();
				free(prompt);
				ft_lstfree_all(const_strings);
				ft_inst_free(insts);
				exit(0);
			}
			else if (ft_strnstr(curr->inst, "export", ft_strlen(curr->inst)) != 0
					&& ft_strlen(curr->inst) == 6)
			{
				int temp_ret;
				if ((temp_ret = ft_export(curr)) != 0)
					printf("error 발생\n");
				printf("ret:%d\n", temp_ret);
			}
			else if (ft_strnstr(curr->inst, "env", ft_strlen(curr->inst)) != 0
					&& ft_strlen(curr->inst) == 3)
			{
				if ((ft_env(curr)) != 0)
					printf("err?\n");
			}
			else if (ft_strnstr(curr->inst, "unset", ft_strlen(curr->inst)) != 0
					&& ft_strlen(curr->inst) == 5)
			{
				if ((ft_unset(curr)) != 0)
					printf("err?\n");
			}
			else if (ft_strnstr(curr->inst, "echo", ft_strlen(curr->inst)) != 0
					&& ft_strlen(curr->inst) == 4)
			{
				if ((ft_echo(curr)) != 0)
					printf("echo err?\n");
			}
			curr = curr->next;
		}
	*/
		ft_lstfree_all(const_strings);
		ft_inst_free(insts);
	}
	free_genv();
	free(prompt);
	return 0;
}
