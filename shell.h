int count_tokens(char * line, char * separator);
char ** parse_args( char * line , char * separator, int size);
void execArgs(char ** args);
void redirectin(char *function, char *destination);
void redirectout(char *function, char *destination);
void forkit(char ** args, int status);
void pipe();
