#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <dirent.h>
#include "shell.h"

// Try starting with these restrictions on input:
// To make your life easier, you could require that all items on the command line are to be separated by a single space.
// When parsing the line, it might help to count the number of tokens (individual pieces), before parsing.
// You can restrict the locations and ordering of > and <.
// You can limit piping (|) to a single pipe.

// counts tokens given a line and separator
int count_tokens( char * line , char * separator){
  int i, count;
  // char * p;
  char c;
  if (line){
    count = 1;
  }
  for (i=0; line[i]; i++){
    c = (line + i)[0];
    // p = &c;
    // printf("c: '%c' |separator: '%s'\n",  c, separator);
    // if (!strcmp(p,separator)){
    if (c == *separator){
      // printf("\tGot it!  c: '%c' |separator: '%s'\n", c, separator);
      count++;
    }
  }
  return count;
}

// parses the args
char ** parse_args( char * line , char * separator, int size ){
  char * curr = line;
  char * token;
  // char s[100]; //to print working directory
  // printf("line: %s\n", line);
  // printf("size line: %d\n", size);
  char ** pointers = calloc((size + 1), sizeof(char *)); //allocate memory for 5 pointers (b/c at most 5 args) + make room for NULL
  int i = 0;
  while (curr){
    // printf("iteration %d | curr: %s | token: %s\n", i, curr, token);
    // pointers[i] = malloc(strlen(line)+1);    // allocate desired memory to each pointer
    token = strsep(&curr, separator);
    // printf("\t\t\ttoken: %s |curr: %s\n", token, curr);
    // Returns the beginning of the original string,
    // sets source to the string starting at 1 index past the location of the new NULL
    if (strcmp(token, "")){ //if not empty string
      // printf("\t\t\t\tAdding token: '%s'\n", token);
      pointers[i] = token;
      i++;
    }

    // printf("iteration %d | curr: %s | token: %s\n", i, curr, token);
    // i++;
  }
  // pointers[i] = "\0";
  return pointers;
}

// Function where the system command is executed
void execArgs(char** args){ //args is already parsed by ';' and ' '
    int status;
    int i;
    char **argscpy = args;
    while (*argscpy){
      char *token = malloc(200); //allocate memory for a token
      strcpy(token, *argscpy);
      // printf("token: '%s'\n", token);
      if (!strcmp(token, "cd")){
        // printing current working directory
        char s[200];
        printf("Current working directory: %s\n", getcwd(s, 100));
        argscpy++;
        strcpy(token, *argscpy);
        if (strcmp(token, "~")){ //if not changing to home dir
          chdir(token);
        }
        else{ //change to homedir
          s = gethome();
          chdir(s);
        }
        if (errno < 0){
          printf("Failed chdir %s\n", strerror(errno));
        }
      }
      else if (!strcmp(token, "exit")){
        printf("Exiting...\n");
        exit(0);
      }
      else if (!strcmp(token, "<")){ //stdin
        redirectin(args, &status, i-1); //i-1 tells the number of args before '<'
      }
      else if (!strcmp(token, ">")){ //stdout
        redirectout(args, &status, i-1); //i-1 tells the number of args before '>'
      }
      // else{
      //   // make the child process
      // }
      i++;
      argscpy++;
    }
    forkit(args, &status);
    return;
}

void redirectin(char **args, int *status, int prevlen){
  char ** prevargs = malloc(2000); // args before <
  int i = 0;
  while (i <= prevlen){ //adding the args to prevlen
    prevargs[i] = args[i];
    i++;
  }
  int backup;
  int fd = open(args[i + 1], O_RDWR | O_EXCL | O_CREAT, 0644);
  //opens with read and write permissions, but creates file if it doesn't exist
  //O_RDWR		open for reading and writing
  //O_CREAT		create file if it does not exist
  //O_EXCL		error if create and file exists
    //if O_EXCL and O_CREAT are set, "open" will fail if the file exists and "errno" will be set to EEXIST.
    //If the file does not exist, "open" will fail and "errno" will be set to EACCESS.
  if (errno < 0){
    printf("Error opening in redirectin: %s\n", strerror(errno));
  }
  if (fd < 0){
    fd = open(args[i + 1], O_RDWR, 0644);
  } //file alredy exists
  backup = dup(0); //stdin is 0
  dup2(fd, 0); //modifying 0 and reading from fd
  forkit(prevargs, status);
  close(fd);
  dup2(backup, 0); //modifying 0 and reading from backup
  // free(i);
  // free(prevlen);
}

void redirectout(char **args, int *status, int prevlen){
  char ** prevargs = malloc(2000); // args before <
  int i = 0;
  while (i <= prevlen){ //adding the args to prevlen
    // printf("args[%d]: %s\n", i, args[i]);
    prevargs[i] = args[i];
    i++;
  }
  // printf("args[%d]: %s\n", i+1, args[i+1]);
    int backup;
    int fd = open(args[i + 1], O_RDWR | O_EXCL | O_CREAT, 0644);
    if (errno < 0){
      printf("Error opening in redirectout: %s\n", strerror(errno));
    }
    if (fd < 0){
      fd = open(args[i + 1], O_RDWR, 0644);
    } //file alredy exists
    backup = dup(1); //stdout is 1
    dup2(fd, 1); //modifying 0 and reading from fd
    forkit(prevargs, status);
    close(fd);
    dup2(backup, 1); //modifying 1 and reading from backup
    // free(i);
    // free(prevlen);
}

void forkit(char ** args, int * status){
  int f = fork();
  if (f < 0) {
      printf("Failed forking child: %s\n", strerror(errno));
      return;
  }
  else if (f == 0) { //child
      if (execvp(args[0], args) < 0) {
        // printf("Failed executing child: %s\n", strerror(errno));
      }
      // printf("child || pid: %d | f: %d | parent: %d\n", getpid(), f, getppid());
      exit(0);
  } else { //parent
      wait(status);

      // if ( WIFEXITED(status) )
      // {
      //     printf("Exit status of the child was %d\n", WEXITSTATUS(status));
      // }
      // printf("parent || wait returned: %d | status: %d | real return value: %d\n", child, status, WEXITSTATUS(status));
      return;
  }
}

char * gethome() {
  char * homedir;
  if ((homedir = getenv("HOME"))){
    pw = getpwuid(getuid());
    return pw->pw_dir;
  }
  return NULL;
}

void pipeit(char *cmd, int * status){
  return;
}
