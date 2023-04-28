#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_pool;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_pool *datash);
} builtin_t;

/* lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* string functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
void rev_string(char *s);

/* memory */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);


/* syntax error */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void syntax_error(data_pool *datash, char *input, int i, int bool);
int check_syntax_error(data_pool *datash, char *input);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(data_pool *datash);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_pool *datash);
int split_commands(data_pool *datash, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(r_var **h, char *in, data_pool *data);
int check_vars(r_var **h, char *in, char *st, data_pool *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_pool *datash);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* execution */
int exec_line(data_pool *datash);
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int check_executable(data_pool *datash);
int check_error_cmd(char *dir, data_pool *datash);
int cmd_exec(data_pool *datash);

/* environment functionality */
char *_getenv(const char *name, char **_environ);
int _env(data_pool *datash);
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_pool *datash);
int _setenv(data_pool *datash);
int _unsetenv(data_pool *datash);

/* directory functionality */
void change_dir_dot(data_pool *datash);
void change_dir_to(data_pool *datash);
void change_dir_to_previous(data_pool *datash);
void home_directory(data_pool *datash);

/* cd_shell.c */
int cd_shell(data_pool *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(data_pool *datash);

/* exit */
int exit_shell(data_pool *datash);

/* _stdlib.c */
int get_len(int n);
char *int_to_char(int n);
int char_to_int(char *s);

/* _error.c */
char *strcat_cd(data_pool *, char *, char *, char *);
char *error_get_cd(data_pool *datash);
char *error_not_found(data_pool *datash);
char *error_exit_shell(data_pool *datash);
char *error_get_alias(char **args);
char *error_env(data_pool *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_pool *datash);
int get_error(data_pool *datash, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* help.c */
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void general_help(void);
void help_exit(void);
void help(void);
void help_alias(void);
void help_cd(void);
int get_help(data_pool *datash);

#endif
