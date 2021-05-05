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

/*
 * 문자열의 왼쪽에서 문자 제거
*/
char	*ft_ltrim(char *str, char c)
{
	char *ptr;

	ptr = str;
	if (!str)
		return (str);
	while (*ptr && *ptr == c)
		ptr++;
	ptr = ft_strdup(ptr);
	free(str);
	return (ptr);
	//return(ptr);
}

/*
 * 문자열의 오른쪽에서 문자 제거
*/
char	*ft_rtrim(char *str, char c)
{
	char *ret;

	ret = str + ft_strlen(str) - 1;
	if (!ret)
		return (ret);
	while (*ret && *ret == c)
	{
		*ret = '\0';
		ret--;
	}
	return (str);
}

char	*ft_trim(char *str, char c)
{
	return (ft_rtrim(ft_ltrim(str, c), c));
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

int cnt_quotes(char *str, char c)
{
	int st;
	int cnt;

	st = 0;
	cnt = 0;
	if (!str)
		return (cnt);
	while (str[st])
	{
		if (str[st] == c)
		{
			if (c == '\'')
				cnt++;
			else if (c == '\"')
			{
				if (st == 0 || (st > 0 && str[st - 1] != '\\'))
					cnt++;
			}
		}
		st++;
	}
	return (cnt);
}

int ft_comma_sub_loop(char **buf, char target)
{
	char *temp;

	// 짝이 맞지 않는 경우
	if (cnt_quotes(*buf, target) % 2 == 1)
	{
		while (1)
		{
			get_next_line(0, &temp, "> ");
			ft_resize_and_copy(buf, "\n", 0, 1);
			ft_resize_and_copy(buf, temp, 0, ft_strlen(temp));
			free(temp);
			if (cnt_quotes(*buf, target) % 2 == 0)
				break ;
		}
	}
	return (0);
}

int merge_str(char **buf, char target)
{
	char *temp;
	char **chunks;
	int cnt;

	cnt = 0;
	temp = 0;
	if (ft_cnt_lines(*buf, target) > 0)
	{
		chunks = ft_split(*buf, target);
		while (*(chunks + cnt))
		{
			ft_resize_and_copy(&temp, *(chunks + cnt), 0, ft_strlen(*(chunks + cnt)));
			cnt++;
		}
		*buf = ft_strdup(temp);
		free(temp);
		ft_free_chunks(chunks, ft_cnt_lines(*buf, target));
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
/*
t_string *ft_lstswap(t_string **root, t_string *now, t_string *to)
{
	t_string *curr;
	t_string *prev;
	t_string *del;

	del = now;
	curr = *root;
	prev = 0;
	while (curr && ft_strnstr(curr->str, now->str, ft_strlen(curr->str)) == 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == 0)
		*root = to;
	else if (to == 0)
		prev->next = curr->next;
	else
		prev->next = to;
	curr = prev;
	if (to != 0)
	{
		curr = to;
		while (curr && curr->next)
			curr = curr->next;
		curr->next = now->next;
	}
	ft_lstfree(del);
	return (curr);
}
*/
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

void ft_inst_add(t_inst **root, t_inst *inst)
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

t_string *replace_str(char **buf, int st, int ed, char *to)
{
	char *temp;
	char *now_str;
	t_string *now;

	temp = 0;
	now_str = 0;
	if (st == ed -1)
		return (0);
	ft_resize_and_copy(&now_str, *buf, st, ed);
	ft_resize_and_copy(&temp, *buf, 0, st + 1);
	ft_resize_and_copy(&temp, to, 0, ft_strlen(to));
	ft_resize_and_copy(&temp, *buf, ed, ft_strlen(*buf));
	now = ft_lstinit(now_str);
	free(*buf);
	*buf = temp;
	return (now);
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
 * -로 시작하면 option으로 인식
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
				if (ft_lstfind(ret->arg, *(space_chunks + k)) == 0)
					ret->option = ft_strdup(*(space_chunks + k));
			}
			else
			{
				arg = ft_lstinit(ft_strdup(*(space_chunks + k)));
				ft_lstadd_back(&ret->arg, arg);
			}
		}
		k++;
	}
	ft_free_chunks(space_chunks, line_cnt);
	return (ret);
}

/*
 * 여러 줄으로 입력받은 명령어 문자열을 |, ; 단위로 split 후 make_command 함수 호출
*/
t_inst *split_commands(char **semi_chunks, int line_cnt)
{
	int i;
	int j;
	char **pipe_chunks;
	t_inst *inst;
	t_inst *root;

	root = 0;
	if (semi_chunks == 0)
		return (0);
	i = 0;
	while (*(semi_chunks + i))
	{
		pipe_chunks = ft_split(*(semi_chunks + i), '|');
		j = 0;
		while (*(pipe_chunks + j))
		{
			inst = make_command(ft_split(*(pipe_chunks + j), ' '), ft_cnt_lines(*(pipe_chunks + j), ' '));
			if (inst == 0)
				printf("err 발생..\n");
			else
			{
				printf("inst:%s\n",inst->inst);
				printf("\toption:%s\n",inst->option);
				for (t_string *r = inst->rd; r; r = r->next)
					printf("\t\trd:%s\n",r->str);
				for (t_string *r = inst->arg; r; r = r->next)
					printf("\t\t\targ:%s\n",r->str);
				ft_inst_add(&root, inst);
			}
			j++;
		}
		ft_free_chunks(pipe_chunks, ft_cnt_lines(*(semi_chunks + i), '|'));
		i++;
	}
	ft_free_chunks(semi_chunks, line_cnt);
	return (root);
}

void processing_quotes(char **buf, t_string **const_strings)
{
	int st;
	int ed;
	t_string *temp;
	char now;

	st = 0;
	while ((now = *(*buf + st)))
	{
		if (now == '\'' || now == '\"')
		{
			ft_comma_sub_loop(buf, now);
			ed = ft_get_next_idx(*buf, now, st + 1);
			while (now == '\"' && *(*buf + ed - 1) == '\\')
				ed = ft_get_next_idx(*buf, now, ed + 1);
			if ((temp = replace_str(buf, st, ed, "%%")) != 0)
				ft_lstadd_back(const_strings, temp);
			st = ft_get_next_idx(*buf, now, st + 1);
		}
		st++;
	}
}

t_string *chunks_to_string(char **chunks)
{
	t_string *ret;
	int i;

	i = 0;
	ret = 0;
	while (*(chunks + i))
		ft_lstadd_back(&ret, ft_lstinit(ft_strdup(*(chunks + (i++)))));
	return (ret);
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
		buf = ft_trim(buf, ' ');
		const_strings = ft_lstinit(0);
		processing_quotes(&buf, &const_strings);
		insts = split_commands(ft_split(buf, ';'), ft_cnt_lines(buf, ';'));
		free(buf);
		t_inst *curr = insts;
		while (curr != 0)
		{
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
					printf("%s: 파일 이나 디렉터리 없음\n", curr->arg->str);

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
			curr = curr->next;
		}
		ft_lstfree_all(const_strings);
		ft_inst_free(insts);
	}
	free_genv();
	free(prompt);
	return 0;
}
