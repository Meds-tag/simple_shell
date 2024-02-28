#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int azefind_builtin(info_t *);
void azefind_cmd(info_t *);
void azefork_cmd(info_t *);

/* path.c */
int azeis_cmd(info_t *, char *);
char *azedup_chars(char *, int, int);
char *azefind_path(info_t *, char *, char *);

/* loophsh.c */
int azeloophsh(char **);

/* err_string_functions.c */
void _azeeputs(char *);
int _azeeputchar(char);
int _azeputfd(char c, int fd);
int _azeputsfd(char *str, int fd);

/* string_functions.c */
int _azestrlen(char *);
int _azestrcmp(char *, char *);
char *azestarts_with(const char *, const char *);
char *_azestrcat(char *, char *);

/* string_functions2.c */
char *_azestrcpy(char *, char *);
char *_azestrdup(const char *);
void _azeputs(char *);
int _azeputchar(char);

/* string_functions3.c */
char *_azestrncpy(char *, char *, int);
char *_azestrncat(char *, char *, int);
char *_azestrchr(char *, char);

/* string_functions4.c */
char **azestrtow(char *, char *);
char **azestrtow2(char *, char);

/* memory_functions */
char *_azememset(char *, char, unsigned int);
void azeffree(char **);
void *_azerealloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int azebfree(void **);

/* more_functions.c */
int azeinteractive(info_t *);
int azeis_delim(char, char *);
int _azeisalpha(int);
int _azeatoi(char *);

/* more_functions2.c */
int _azeerratoi(char *);
void azeprint_error(info_t *, char *);
int azeprint_d(int, int);
char *azeconvert_number(long int, int, int);
void azeremove_comments(char *);

/* builtin_emulators.c */
int _azemyexit(info_t *);
int _azemycd(info_t *);
int _azemyhelp(info_t *);

/* builtin_emulators2.c */
int _azemyhistory(info_t *);
int _azemyalias(info_t *);

/* getline.c module */
ssize_t azeget_input(info_t *);
int _azegetline(info_t *, char **, size_t *);
void azesigintHandler(int);

/* info.c module */
void azeclear_info(info_t *);
void azeset_info(info_t *, char **);
void azeree_info(info_t *, int);

/* env.c module */
char *_azegetenv(info_t *, const char *);
int _azemyenv(info_t *);
int _azemysetenv(info_t *);
int _azemyunsetenv(info_t *);
int azepopulate_env_list(info_t *);

/* env2.c module */
char **azeget_environ(info_t *);
int _azeunsetenv(info_t *, char *);
int _azesetenv(info_t *, char *, char *);

/* file_io_functions.c */
char *azeget_history_file(info_t *info);
int azewrite_history(info_t *info);
int azeread_history(info_t *info);
int azebuild_history_list(info_t *info, char *buf, int linecount);
int azerenumber_history(info_t *info);

/* liststr.c module */
list_t *azeadd_node(list_t **, const char *, int);
list_t *azeadd_node_end(list_t **, const char *, int);
size_t azeprint_list_str(const list_t *);
int azedelete_node_at_index(list_t **, unsigned int);
void azefree_list(list_t **);

/* liststr2.c module */
size_t azelist_len(const list_t *);
char **azelist_to_strings(list_t *);
size_t azeprint_list(const list_t *);
list_t *azenode_starts_with(list_t *, char *, char);
ssize_t azeget_node_index(list_t *, list_t *);

/* chain.c */
int azeis_chain(info_t *, char *, size_t *);
void azecheck_chain(info_t *, char *, size_t *, size_t, size_t);
int azereplace_alias(info_t *);
int azereplace_vars(info_t *);
int azereplace_string(char **, char *);

#endif
