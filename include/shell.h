#ifndef EVAL_HEADER
#define EVAL_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>

#define STRNULL ""
#define MAX_COMMAND_LENGTH 200
#define MAX_NUM_ARGUMENTS 10
#define MAX_ARGS 200
#define MAX_ARG_LEN 10

struct __args {
    int arg_count;
    char arg[MAX_ARG_LEN];
    int arg_pos;
    int quote_flag;
	int i;
};

struct __shell {
	
	enum {
		waiting,
		action,
		quit,
		notwork
	} state;
	
	char* currentdirpath;
};

void prompt();
int startWith(const char *str, const char *prefix);
struct __args split_args(char* input, char** output);
int evalCD(struct __shell* shell, char* input);
int evalLS(struct __shell* shell);

#endif