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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	ed;
	size_t	st;

	if (!s)
		return (0);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	st = 0;
	if (ft_strlen(s) >= (size_t)start)
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
			cnt++;
		st++;
	}
	return (cnt);
}

int ft_comma_sub_loop(char **buf, char target)
{
	char *temp;
	int	cnt;

	cnt = 0;
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
}



void ft_lst_free(t_string *root)
{
	t_string *del;

	del = root;
	while (del)
	{
		root = del->next;
		free(del->str);
		free(del);
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
		ft_lst_free(del->arg);
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
	temp->idx = -1;
	temp->str = s;
	temp->next = 0;
	return (temp);
}

void ft_lst_add(t_string **root, t_string *s)
{
	t_string *curr;
	int cnt;

	cnt = 1;
	if (*root == 0)
	{
		s->idx = 1;
		*root = s;
	}
	else
	{
		curr = *root;
		while (curr->next != 0)
		{
			cnt++;
			curr = curr->next;
		}
		s->idx = cnt;
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
	ret->option = 0;
	ret->arg = 0;
	ret->next = 0;
	return (ret);
}

/*
 * 추후 명령어부분 및 인자에서 redireciton이 있는지 체크
*/
void check_redirection()
{
	// stub
	int k = 0;	char **space_chunks = 0;

	if (ft_strchr(*(space_chunks + k), '>') != 0)
	{
		if (ft_strnstr(*(space_chunks + k), ">>", ft_strlen(*(space_chunks + k)) != 0))
		{
			// redirection (output, append mode)
		}
		else
		{
		// redirection (output)
		}
	}
	else if (ft_strchr(*(space_chunks + k), '<') != 0)
	{
		// redirection (input)
	}
}

/*
 * 하나의 명령어이므로 space 단위로 split한 후 첫 번째는 명령어,
 * 두 번째는 '-'로 시작하면 옵션 그 외에는 인자로 넣어줌
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
		// -로 시작하면 옵션으로 인식
		if (ft_get_next_idx(*(space_chunks + k), '-', 0) == 0)
			ret->option = ft_strdup(*(space_chunks + k));
		else
		{
			arg = ft_lst_init(ft_strdup(*(space_chunks + k)));
			ft_lst_add(&ret->arg, arg);
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
			//printf("inst:%s, op:%s\n", inst->inst, inst->option);
			ft_inst_add(&root, inst);
			j++;
		}
		ft_free_chunks(pipe_chunks, ft_cnt_lines(*(semi_chunks + i), '|'));
		i++;
	}
	ft_free_chunks(semi_chunks, line_cnt);
	return (root);
}

int main(int argc, char **argv, char **envp){
	char *buf;
	char *prompt;
	t_inst *insts;
	t_string *const_strings;
	t_string *temp;
	int st;

	prompt = get_prompt();
	while (1)
	{
		get_next_line(0, &buf, prompt);
		buf = ft_trim(buf, ' ');
		st = 0;
		const_strings = ft_lst_init(0);
		while (buf[st])
		{
			if (buf[st] == '\'' || buf[st] == '\"')
			{
				ft_comma_sub_loop(&buf, buf[st]);
				if ((temp = replace_str(&buf, st, ft_get_next_idx(buf, buf[st], st + 1), "%%")) != 0)
				ft_lst_add(&const_strings, temp);
				st = ft_get_next_idx(buf, buf[st], st + 1);
			}
			st++;
		}
		insts = split_commands(ft_split(buf, ';'), ft_cnt_lines(buf, ';'));
		free(buf);
		t_inst *curr = insts;
		while (curr)
		{
			//printf("inst:|%s| option:|%s|\n", curr->inst, curr->option);
			t_string *args = curr->arg;
			/*
			int i = 0;
			while (args)
			{
				printf("%dth:|%s|,\n",i++, args->str);
				args = args->next;
			}
			curr = curr->next;
			*/
		}
		ft_lst_free(const_strings);
		ft_inst_free(insts);
	}
	free(prompt);
	return 0;
}
