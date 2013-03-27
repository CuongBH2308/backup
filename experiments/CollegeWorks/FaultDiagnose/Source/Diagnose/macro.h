#define		SUCCESS		1
#define		FAILURE		0
#define		STR_END		'\0'
#define		NONE		-1
#define		LINE_LENGTH		300
#define		NULL_STR	""
#define		STACK_COUNT 100

/*对字符串的操作string_opr.c*/
extern	char	*nli_get_compact_string(char	*);
extern	int		nli_start_with_string(char *,char *);
extern	int		nli_end_with_string(char *, char *);
extern	char	* nli_trim(char	*);
extern	int		nli_is_white_space(char *, int);
extern	char	* nli_sub_string_tail(char *, int);
extern	char	* nli_sub_string_middle(char *, int , int);
extern	char	* nli_replace_with_string(char *, char *, char *);
extern	int		nli_index_of_string(char *, char *);
extern	int		nli_last_index_of_string(char *, char *);
extern	char	* nli_expand_string(char	*, float);
extern	char	* nli_del_char(char *, char);
/*比较两个字符串，忽略大小写的差别*/
extern int strcmp_ignore_case( char *, char *);
extern char *get_str_from_char(char, char *,int);
extern char *get_str_from_str(char *,int,char *,int);
