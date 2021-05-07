#include "minishell.h"

# define DIRTYPE_TO_STRING(X) \
				((X) == DT_DIR ? "directory" : \
				 (X) == DT_REG ? "regular file" : \
				 					"unknown file")

char *find_value(char *key, char **environ)
{
	int	i;

	i = -1;
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], key, ft_strlen(key)))
			return (environ[i] + ft_strlen(key) + 1);
	}
	return ("");
}

char *find_path(char *cmdline, char **environ)
{
	int i;
	char *temp;
	char *new_path;
	char **paths;
	struct stat	s;

	temp = find_value("PATH", environ);
	paths = ft_split(temp, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", cmdline);
		new_path = ft_strjoin(paths[i], temp);
		free(temp);
		if (stat(new_path, &s) == 0)
			return (new_path);
		free(new_path);
	}
	return (ft_strdup(cmdline));
}

void exec_child_process(char **cmd)
{
	char *path;

	printf("hello child\n");
	path = find_path("ls", environ);
	if (execve(path, cmd, environ) == 1);
		printf("%s\n", strerror(errno));
	printf("child end\n"); // 명령을 못찾으면 이부분부터 실행되지않음
	exit(0);
}

int main(int argc, char *argv[], char* envp[])
{
	pid_t pid;
	int status;
	char **arg;


// cd 와 errno 테스트
	// char path[256];
	// printf("default errno: %d\n", errno);
	// memset(path, 0, 256);
	// if (getcwd(path, 256) == NULL)
	// {
	// 	printf("%s", strerror(errno));
	// 	return (-1);
	// }
	// printf("Before chdir, current path : %s\n", path);
	// if (chdir("..") == -1)
    // {
    //     printf("%s", strerror(errno));
    //     return (-1);
    // }
    // if (getcwd(path, 256) == NULL)
    // {
    //     printf("%s", strerror(errno));
    //     return (-1);
    // }
	// printf("after chdir, current path : %s\n", path);
	// if (chdir("invalid_path") == -1)
	// {
	// 	printf("errno: %d\n", errno);
	// 	printf("%s\n", strerror(errno));
    //     return (-1);
	// }
	// printf("invalid_path : %s\n", path);

// fork 후 외부파일 실행해보기
// waitpid 함수에 인자로 WNOHANG 사용시 논블록킹으로 작동함
// 그래서 while문이랑 사용가능 기존 wait는 무조건 자식이 끝날때까지 블로킹
	// status = 1;
	// arg = (char **)malloc(sizeof(char *) * 3);
	// arg[0] = "ls";
	// arg[1] = "-al";
	// arg[2] = NULL;
	// pid = fork();
	// if (pid == 0)
	// 	exec_child_process(arg);
	// while(!(waitpid(pid, &status, WNOHANG));
	// if (WIFEXITED(status)) //WIFEXITED 비정상 종료시 non-zero 리턴
	//	  printf("child procees exited number: %d\n", WEXITSTATUS(status)); // WEXITSTATUS exited number
	// else
	//	  printf("is not exited\n");
	// printf("%d\n", status);
	// printf("this is end\n");
	// free(arg);

//  표준 입출력fd를 close한후 다시 open 할수있는 방법은 없는건지 궁금
	// int fd1;
	// int fd2;
	// int ret1;

	// fd1 = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// printf("fd1: %d\n", fd1);
	// write(fd1, "init\n", 5);
	// //fd2 = STDOUT_FILENO;
	// fd2 = STDIN_FILENO;
	// ret1 = dup2(fd1, fd2);
	// printf("fd1: %d, fd2: %d, ret1: %d\n", fd1, fd2, ret1);
	// write(fd1, "fd1\n", 4);
	// write(ret1, "re1\n", 4);
	// close(ret1);
	// write(fd2, "fd2\n", 4);
	// printf("fd1: %d, fd2: %d, ret1: %d\n", fd1, fd2, ret1);


// 파일정보 알아내기
	// DIR *p_dir;
	// if ((p_dir = opendir(path)) == NULL)
	// {
	// 	printf("fail opendir()\n");
	// 	return (-1);
	// }

    // struct dirent *dir_ent;
    // while ((dir_ent = readdir(p_dir)) != NULL)
    // {
    //     printf("*****************************************\n");
    //     printf("d_name : %s\n", dir_ent->d_name);
    //     printf("d_type : %s\n", DIRTYPE_TO_STRING(dir_ent->d_type));
    //     printf("*****************************************\n");
    // }
 
    // if (closedir(p_dir) == -1)
    // {
    //     printf("fail closedir()\n");
    //     return (-1);
    // }

// // 정리 regular file stat_buf.st_mode = 33188
// // derectory stat_buf.st_mode = 16877 함수 만들어서 쓰면됨
//	struct stat stat_buf;
// 	stat("test.c", &stat_buf);
// 	printf("file size of test.txt: %ld\n", stat_buf.st_size);
// 	printf("%d\n", stat_buf.st_mode);
// 	    if (S_ISDIR(stat_buf.st_mode))
//         printf("text.txt is directory\n");
//     else if (S_ISREG(stat_buf.st_mode))
//         printf("test.xt is regular file\n");
//     else
//         printf("else\n");

    int        prcw[2]; /* parent read, child write */
    int        pwcr[2]; /* parent write, child read */
    char    res[10];
 
    if (pipe(prcw) || pipe(pwcr))
    {
        printf("pipe error: %s\n", strerror(errno));
        return (-1);
    }
    pid = fork();
    if (pid > 0) /* parent */
    {
        write(pwcr[1], "Parent", 6);
        memset(res, 0, 10);
        read(prcw[0], res, 5); res[5] = 0;
        printf("Parent Process: %s\n", res);
        while (!waitpid(pid, &status, WNOHANG));
    }
    else if (pid == 0) /* chlid */
    {
        write(prcw[1], "Child", 5);
        memset(res, 0, 10);
        read(pwcr[0], res, 6); res[6] = 0;
        printf("Chlid Process: %s\n", res);
    }
    else
    {
        printf("fork error\n");
        return (-1);
    }
    printf("end\n");


	return (0);
}