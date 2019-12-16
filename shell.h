int count_tokens(char * line, char * separator);
char ** parse_args( char * line , char * separator, int size);
void execArgs(char ** args);
void redirectin(char **args, int * status, int prevlen);
void redirectout(char **args, int * status, int prevlen);
void forkit(char ** args, int * status);
char * gethome();
void pipeit(char *cmd);
