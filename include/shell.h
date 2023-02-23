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
#define MAX_NUM_ARGUMENTS 200
#define MAX_ARGS 200
#define MAX_ARG_LEN 200

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
char* getClipBoard();
int startWith(const char *str, const char *prefix);
int split_args(char input[MAX_ARGS], char** output);
int evalCD(struct __shell* shell, char input[MAX_ARGS]);
int evalPaste();
int evalCL(struct __shell* shell);
int evalLS(struct __shell* shell);

#endif