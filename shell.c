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
  char s[100]; //to print working directory
  // printf("line: %s\n", line);
  // printf("size line: %d\n", size);
  char ** pointers = malloc((size + 1) * sizeof(char *)); //allocate memory for 5 pointers (b/c at most 5 args) + make room for NULL
  int i = 0;
  while (curr){
    // printf("iteration %d | curr: %s | token: %s\n", i, curr, token);
    // pointers[i] = malloc(strlen(line)+1);    // allocate desired memory to each pointer
    token = strsep(&curr, separator);
    // printf("\t\t\ttoken: %s |curr: %s\n", token, curr);
    // Returns the beginning of the original string,
    // sets source to the string starting at 1 index past the location of the new NULL
    if (strcmp(token, "")){
      // printf("\t\t\t\tAdding token: '%s'\n", token);
      pointers[i] = token;
      i++;
    }
    if (!strcmp(token, "cd")){
      // printing current working directory
      printf("%s\n", getcwd(s, 100));
      token = strsep(&curr, separator); //takes next arg for cd
      pointers[i] = token;
      i++;
      chdir(token);
      if (errno < 0){
        printf("Failed chdir %s\n", strerror(errno));
      }
    }
    else if (!strcmp(token, "exit")){
      printf("Exiting...\n");
      exit(0); //for some reason, this only exits if you remain in the current directory
    }
    else if (!strcmp(token, ">")){
      token = strsep(&curr, separator);
      pointer[i] = token;
      i++;
      redirectout(pointers[i-2], token[i-1], token);
    }
    else if (!strcmp(token, "<")){
      token = strsep(&curr, separator);
      pointer[i] = token;
      i++;
      redirectin(pointers[i-2], token);
    }
    // printf("iteration %d | curr: %s | token: %s\n", i, curr, token);
    // i++;
  }
  return pointers;
}

// Function where the system command is executed
void execArgs(char** args){
    // make the child process
    int child;
    int status;

    int f = fork();

    if (f < 0) {
        printf("Failed forking child: %s\n", strerror(errno));
        return;
    }
    else if (f == 0) { //child
        if (execvp(args[0], args) < 0) {
          printf("Failed executing child: %s\n", strerror(errno));
        }
        // printf("child || pid: %d | f: %d | parent: %d\n", getpid(), f, getppid());
        exit(0);
    } else { //parent
        child = wait(&status);

        // if ( WIFEXITED(status) )
        // {
        //     printf("Exit status of the child was %d\n", WEXITSTATUS(status));
        // }
        // printf("parent || wait returned: %d | status: %d | real return value: %d\n", child, status, WEXITSTATUS(status));
        return;
    }
}

void redirectin(char *function, char *destination){
  int fd = open(destination, 0_RDWR);
  if (errno < 0){
    printf("Error opening in readirectin: %s\n", strerror(errno));
  }
  backup = dup(0); //stdin is 0
  dup2(backup, 0); //modifying 0 and reading from backup
}
void redirectout(char *function, char *destination){
    int fd = open(destination, 0_RDWR);
    if (errno < 0){
      printf("Error opening in readirectin: %s\n", strerror(errno));
    }
    backup = dup(1); //stdout is 1
    dup(fd, 1);
    dup2(backup, 1); //modifying 1 and reading from backup
}
