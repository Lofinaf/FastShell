#include "../include/shell.h"

void prompt() {
	struct __shell Terminal;
	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	char input[MAX_COMMAND_LENGTH];
	
	time_t current;
	int year, month, day, hour, second;
	
	time(&current);
	
    SetConsoleTextAttribute(console, 10);
	printf("FastShell ");
    SetConsoleTextAttribute(console, 9);
	printf("%s \n", ctime(&current));
	SetConsoleTextAttribute(console, 15);
    while (1) {
        printf("> ");
        fgets(input, MAX_COMMAND_LENGTH, stdin);
		
		SetConsoleTextAttribute(console, 10);
		printf("\n");
		printf("Action %s", input);
		SetConsoleTextAttribute(console, 15);
		
		if (strcmp(input, "q\n") == 0 || strcmp(input, "quit\n") == 0) {
            break;
        }
		
		if (strcmp(input, "ls\n") == 0) {
            evalLS(&Terminal);
        }
		
		if (startWith(input, "cd") != 0) {
			evalCD(&Terminal, &input);
		}
		
		printf("\n");
    }
}

int startWith(const char *str, const char *prefix) {
    size_t str_len = strlen(str);
    size_t prefix_len = strlen(prefix);

    if (prefix_len > str_len) {
        return 0;
    }

    return strncmp(str, prefix, prefix_len) == 0;
}

struct __args split_args(char* input, char** output) {
    int arg_count = 0;
    char arg[MAX_ARG_LEN];
    int arg_pos = 0;
    int quote_flag = 0;
    int i = 0;
  
    while (input[i] != '\0') {
        if (isspace(input[i]) && !quote_flag) {
            if (arg_pos > 0) {
                arg[arg_pos] = '\0';
                output[arg_count] = strdup(arg);
                arg_count++;
                arg_pos = 0;
            }
        } else if (input[i] == '"' && !quote_flag) {
            quote_flag = 1;
        } else if (input[i] == '"' && quote_flag) {
            quote_flag = 0;
            if (arg_pos > 0) {
                arg[arg_pos] = '\0';
                output[arg_count] = strdup(arg);
                arg_count++;
                arg_pos = 0;
            }
        } else {
            arg[arg_pos] = input[i];
            arg_pos++;
        }
        i++;
    }
    
    if (arg_pos > 0) {
        arg[arg_pos] = '\0';
        output[arg_count] = strdup(arg);
        arg_count++;
    }
    
    output[arg_count] = NULL;
    
	struct __args args = {arg_count, arg, arg_pos, quote_flag, i};
    return args;
}

int evalCD(struct __shell* shell, char* input) {
	char** Output;
	struct __args args = split_args(&input, &Output); 
	if (args->arg_count < 2) {
		fprintf(stderr, "Usage: cd directory\n");
		return 1;
	}
    return 0;
}

int evalLS(struct __shell* shell) {
	shell->state = action;
	if (shell->currentdirpath == STRNULL) { shell->state = waiting; return 1; }
	
    DIR *dir;
    struct dirent *entry;

    dir = opendir(shell->currentdirpath);
	
    if (!dir) {
        perror("diropen");
        return 1;
    };

    while ( (entry = readdir(dir)) != NULL) {
        printf("%d - %s [%d] %d\n",
            entry->d_ino, entry->d_name, entry->d_reclen);
    };

    closedir(dir);

	return 0;
}