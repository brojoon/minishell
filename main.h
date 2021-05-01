// 1개 명령어 struct
typedef struct s_inst t_inst;
typedef struct s_string t_string;
struct s_inst
{
	char *inst;
	char *option;
	t_string *arg;
	t_inst *next;
};

struct s_string
{
	int idx;
	char *str;
	t_string *next;
};
