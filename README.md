# CShell
Making a shell in C
Rachel Leong Period 10 </br>
# Features

* Forks and executes commands
* Parses multiple commands on one line using ';'
* Redirects using > and <
* Simple piping works

# Attempted
* Pipes didn't work
* Multiple redirection didn't work

# Bugs
* Occasionally tr a-z A-Z < foo gives an error saying that there are too many arguments for tr
* Although it will pipe, ls | wc says that it can't cd into "|"
* Occasionally cat > output says that ">" isn't a valid file or directory

# Extras
* Functions work when you add extra ';'s or ' 's in between
* You can easily cd into the home directory with 'cd ~'

# Function Headers
int count_tokens(char * line, char * separator); </br>
* Takes an input from the shell and separates it based on a single character separator.</br>
* Returns the number of tokens </br>
char ** parse_args( char * line , char * separator, int size); </br>
* Given the line and separator and size, the number of tokens from count_tokens, it will parse the arguments with ";" and " " and split it into tokens. </br>
* Returns an array of strings (parsed arguments) </br>

void execArgs(char ** args); </br>
* Takes parsed arguments and runs the functions with execvp </br>
* Returns nothing </br>

void redirectin(char **args, int * status, int prevlen); </br>
* Takes parsed arguments, status for waiting, and prevlen is the number of tokens prior to '>' </br>
* Returns nothing </br>

void redirectout(char **args, int * status, int prevlen); </br>

* Takes parsed arguments, status for waiting, and prevlen is the number of tokens prior to '<' </br>
* Returns nothing

void forkit(char ** args, int * status); </br>
* Forks a child process given args (parsed arguments) and status for waiting </br>
* Returns nothing

char * gethome(); </br>
* Gets the home directory </br>
* Returns a pointer to a string contining the home directory

void pipeit(char **args, int * status, int prevlen); </br>
* Was supposed to take a simple pipe given the parsed args, a status for waiting, and prevlen which is the number of tokens prior to '|' </br>

#Files
shell.c </br>
* Contains all shell functions </br>
main.c </br>
* Takes an input from the user, parses it, and forks and executes the commands
shell.h </br>
* Header file for all shell functions
