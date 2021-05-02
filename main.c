#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
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
	//printf("%s\n", prompt);
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

t_string *ft_lst_find(t_string *root, char *target)
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
	else
		prev->next = to;
	curr = to;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = now->next;
	ft_lstfree(del);
	return (curr);
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

t_string *ft_lst_init(char *s)
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
	now = ft_lst_init(now_str);
	free(*buf);
	*buf = temp;
	return (now);
}

t_inst *ft_inst_init()
{
	t_inst *ret;

	if (!(ret = (t_inst *)malloc(sizeof(t_inst))))
		return (0);
	ret->inst = 0;
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
 * 하나의 명령어이므로 space 단위로 split한 후 첫 번째는 명령어,
 * 나머지는 인자로 넣어줌 ( - 옵션이 붙은 경우에는 중복 체크하여 한개만)
*/
t_inst *make_command(char **space_chunks, int line_cnt)
{
	int k;
	t_inst *ret;
	t_string *arg;

	ret = ft_inst_init();
	ret->inst = ft_strdup(*space_chunks);
	k = 1;
	while (*(space_chunks + k))
	{
		if (ft_strchr(*(space_chunks + k), '-') == *(space_chunks + k))
		{
			if (ft_lst_find(ret->arg, *(space_chunks + k)) != 0)
			{
				k++;
				continue ;
			}
		}
		arg = ft_lst_init(ft_strdup(*(space_chunks + k)));
		ft_lstadd_back(&ret->arg, arg);
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
			//printf("inst:%s\n", inst->inst);
			ft_inst_add(&root, inst);
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
		ft_lstadd_back(&ret, ft_lst_init(ft_strdup(*(chunks + (i++)))));
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
	if (num_of_lines == 2 && num_of_lines2 == 2)
		return (1);
	return (0);
}

/*
 * 명령어 부분에 있는 redirection 처리 부분
 * 명령어에서 redirection이 두개 이상 
*/
int split_inst_red(t_inst *curr)
{
	char *rd;
	char **inst_chunks;
	t_string *temp_args;
	int num_of_lines;

	rd = 0;
	if (check_red_error(curr->inst) == 1)
		return (1);
	if ((inst_chunks = split_redirection(curr->inst, &rd)) != 0)
	{
		num_of_lines = ft_cnt_lines(curr->inst, rd[0]);
		free(curr->inst);
		curr->inst = ft_strdup(*inst_chunks);
		temp_args = chunks_to_string(inst_chunks + 1);
		ft_lstadd_front(&temp_args, ft_lst_init(ft_strdup(rd)));
		ft_lstadd_back(&temp_args, curr->arg);
		curr->arg = temp_args;
		ft_free_chunks(inst_chunks, num_of_lines);
	}
	return (0);
}
/*
 * argument에 있는 redirection은 >2 , 1>2, 1>, 1<2>>3 형식이며
 * 1>, 1<2>>3은 error로 처리
*/
int split_args_red(t_inst *curr)
{
	t_string *curr_arg;
	char **arg_chunks;
	char *rd;
	t_string *temp_args;

	curr_arg = curr->arg;
	rd = 0;
	while (curr_arg)
	{
		if (check_red_error(curr_arg->str) == 1)
			return (1);
		if ((arg_chunks = split_redirection(curr_arg->str, &rd)) != 0)
		{
			temp_args = chunks_to_string(arg_chunks);
			if (ft_strnstr(curr_arg->str, rd, ft_strlen(curr_arg->str)) == curr_arg->str)
				ft_lstadd_front(&temp_args, ft_lst_init(ft_strdup(rd)));
			else if (ft_cnt_lines(curr_arg->str, rd[0]) == 1)
			{
				if (ft_strnstr(curr_arg->str, rd, ft_strlen(curr_arg->str))[1] == 0)
				{
					ft_free_chunks(arg_chunks, ft_cnt_lines(curr_arg->str, rd[0]));
					ft_lstfree_all(temp_args);
					return (1);
				}
				ft_lstadd_back(&temp_args, ft_lst_init(ft_strdup(rd)));
			}
			else
				ft_lstadd_after(&temp_args, ft_lst_init(ft_strdup(rd)));
			ft_free_chunks(arg_chunks, ft_cnt_lines(curr_arg->str, rd[0]));
			curr_arg = ft_lstswap(&(curr->arg), curr_arg, temp_args);
		}
		curr_arg = curr_arg->next;
	}
	return (0);
}

int main(int argc, char **argv, char **envp){
	char *buf;
	char *prompt;
	t_inst *insts;
	t_string *const_strings;

	(void)argc;
	(void)argv;
	(void)envp;
	prompt = get_prompt();
	while (1)
	{
		get_next_line(0, &buf, prompt);
		buf = ft_trim(buf, ' ');
		const_strings = ft_lst_init(0);
		processing_quotes(&buf, &const_strings);
		insts = split_commands(ft_split(buf, ';'), ft_cnt_lines(buf, ';'));
		free(buf);
		t_inst *curr = insts;
		while (curr != 0)
		{
			if (split_args_red(curr) == 1 || split_inst_red(curr) == 1)
			{
				// parsing error
				break ;
			}
			printf("inst:|%s|\n", curr->inst);
			int i = 0;
			t_string *args = curr->arg;
			while (args)
			{
				printf("%dth:|%s|\n",i++, args->str);
				args = args->next;
			}
			curr = curr->next;
		}
		ft_lstfree_all(const_strings);
		ft_inst_free(insts);
	}
	free(prompt);
	return 0;
}
