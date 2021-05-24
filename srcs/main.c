/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:02:06 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 13:17:57 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 프롬프트는 cwd를 가져와서 출력
*/

char	*get_prompt(void)
{
	char	buf[BUFFER_SIZE];
	char	*buf_ptr;
	char	*prompt;

	buf_ptr = getcwd(buf, 1024);
	prompt = ft_strdup(buf_ptr);
	ft_resize_and_copy(&prompt, " % ", 0, 3);
	return (prompt);
}

void	init_term(t_cursor *cursor)
{
	tcgetattr(STDIN_FILENO, &(cursor->term));
	cursor->term.c_lflag &= ~ICANON;
	cursor->term.c_lflag &= ~ECHO;
	cursor->term.c_cc[VMIN] = 1;
	cursor->term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &(cursor->term));
	tgetent(NULL, "xterm");
	cursor->cm = tgetstr("cm", 0);
	cursor->ce = tgetstr("ce", 0);
}

t_inst	*main_subloop(char *prompt, t_cursor *cursor, t_env *env_root)
{
	char		*buf;
	t_inst		*insts;
	t_string	*const_strings;

	if (get_next_line(0, &buf, prompt, cursor) == 9999)
	{
		free_genv(env_root);
		recover_term(cursor);
		exit(1);
	}
	const_strings = 0;
	handle_quotes(&buf, &const_strings, cursor);
	insts = split_commands(ft_split(buf, ';'), ft_cnt_lines(buf, ';'));
	proc_consts(env_root, &const_strings);
	proc_inst_metachar(env_root, &insts);
	if (const_strings)
		get_ori_consts(const_strings, &insts);
	free(buf);
	ft_lstfree_all(const_strings);
	return (insts);
}

int		main(int argc, char **argv, char **envp)
{
	char		*prompt;
	t_env		*env_root;
	t_inst		*insts;
	t_cursor	cursor;

	env_root = 0;
	set_signal();
	set_genv(&env_root, envp);
	cursor.history = 0;
	(void)argc;
	(void)argv;
	while (1)
	{
		init_term(&cursor);
		prompt = get_prompt();
		insts = main_subloop(prompt, &cursor, env_root);
		free(prompt);
		exec_parent_process(insts, &env_root, &cursor);
		ft_inst_free(insts);
	}
	free_genv(env_root);
	recover_term(&cursor);
	return (0);
}
