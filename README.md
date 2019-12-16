# CShell
Making a shell in C
Rachel Leong Period 10 </br>
**Assignment** </br>
Read a line at a time, parse the line to separate the command from its arguments. It should then fork and exec the command. The parent process should wait until the exec'd program exits and then it should read the next command. </br>
* Note: exit and cd cannot be run through a forked child process, you will have to implement these commands on your own. <br>
check out the chdir() function
1. Read and separate multiple commands on one line with ;. That is, the line ls -l ; echo hello should first run the command ls -l and then echo hello.  
2. Implement simple redirection using > (redirecting stdout) and < (redirecting stdin). - This will be explained in class.
3. Implement simple pipes, that is: ls | wc would run ls and use the output from ls as the input for wc. - This will be explained in class.
* Check out popen() for this.
4. All of these commands work in bash, so use it to check out the functionality of each feature if you are unclear about anything.

*Specific requirements*
1. Every function you write must have a function header describing the arguments, return value and what the function does.
* Use modular design liberally. This is a large program.
2. You should have a readme file with the following:
<br>    i. A description of what features your shell implements
<br>   ii. A description of what features you attempted to implement but were unsuccessful
<br>  iii. Any bugs or things you want me to know about your program
<br>   iv. I am much more forgiving of reported bugs than bugs I discover while testing
<br>    v. A copy of every function header
<br>   vi. An example of the readme file can be found in the github repository for this assignment
3. This project should use separate C files as necessary.
4. The project should be built using make and a makefile, I will only compile by using make.
</br>

Try starting with these restrictions on input: <br>
1. To make your life easier, you could require that all items on the command line are to be separated by a single space.
2. When parsing the line, it might help to count the number of tokens (individual pieces), before parsing.
3. You can restrict the locations and ordering of > and <.
4. You can limit piping (|) to a single pipe.
If you would like to implement other features after getting these ones down, please do. Look at what bash does and see what else you can do!

# Instructions
int count_tokens(char * line, char * separator); </br>
* Takes an input from the shell and separates it based on a single character separator.
* Returns the number of tokens </br>
char ** parse_args( char * line , char * separator, int size); </br>
* Given the line and separator and size, the number of tokens from count_tokens, it will parse the arguments with ";" and " " and split it into tokens.
* Returns an array of strings (parsed arguments) </br>
void execArgs(char ** args); </br>
* Takes parsed arguments and runs the functions with execvp </br>

void redirectin(char **args, int * status, int prevlen); </br>
* takes parsed arguments, status for waiting, and prevlen is the number of tokens prior to > </br>

void redirectout(char **args, int * status, int prevlen); </br>
* takes parsed arguments, status for waiting, and prevlen is the number of tokens prior to < </br>

void forkit(char ** args, int * status); </br>
* forks a child process given args (parsed arguments) and status for waiting

char * gethome(); </br>
* gets the home directory

void pipeit(char *cmd); </br>
* makes a simple pipe given a command
