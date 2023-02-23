#include "../include/shell.h"

void prompt() {
	struct __shell Terminal;
	Terminal.currentdirpath = "C:/Windows/System32";
	
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
		
		if (strcmp(input, "p\n") == 0) {
			evalPaste();
		}

		if (strcmp(input, "cl\n") == 0) {
			evalCL(&Terminal);
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

int split_args(char input[MAX_ARGS], char** output) {
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
    
    return arg_count;
}

int evalCL(struct __shell* shell) {
	printf("\n%s", shell->currentdirpath);
}

int evalCD(struct __shell* shell, char input[MAX_ARGS]) {
	char* args[MAX_ARGS];
	int arg_count = split_args(input, args);
	
	printf("Number of arguments: %d\n", arg_count);
    
    for (int i = 0; i < arg_count; i++) {
        printf("Argument %d: '%s'\n", i, args[i]);
    }
	
	shell->currentdirpath = args[1];
    return 0;
}

char* getClipBoard() {
    if (OpenClipboard(NULL)) {
        HANDLE hData = GetClipboardData(CF_TEXT);
        char *buffer = (char*) GlobalLock(hData);
        printf("Clipboard contents: %s\n", buffer);
        GlobalUnlock(hData);
        CloseClipboard();
		return buffer;
    } else {
        printf("Failed to open clipboard\n");
    }
}

int evalPaste() {
	printf("\n%s", getClipBoard());
}

int evalLS(struct __shell* shell) {
	shell->state = action;
	if (shell->currentdirpath == STRNULL) { shell->state = waiting; return 1; }
	
    DIR *dir;
    struct dirent *entry;

    dir = opendir(shell->currentdirpath[0]);
	
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