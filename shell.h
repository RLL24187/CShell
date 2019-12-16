int count_tokens(char * line, char * separator);
char ** parse_args( char * line , char * separator, int size);
void execArgs(char ** args);
void redirectin(char *function, int * status);
void redirectout(char *function, int * status);
void forkit(char ** args, int * status);
void pipe();
