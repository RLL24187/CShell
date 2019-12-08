// #include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <errno.h>
#include <unistd.h>
// #include <sys/stat.h>
// #include <time.h>
// #include <dirent.h>
#include "shell.h"

int main(){

  char line[100];
  char * separator;
  char ** args;
  int f = fork();
  if (f){

    // line
    separator = " ";
    strcpy(line, "ls -l -a");
    printf("Testing parse_args (run '%s'):\n", line);

    args = parse_args( line , separator, count_tokens(line, separator));

    execvp(args[0], args);
    return 0;
  }
  else{

    strcpy(line, "ls -l -a -r");
    printf("Testing parse_args (run '%s')\n", line);

    args = parse_args( line , separator, count_tokens(line, separator));

    execvp(args[0], args);
    return 0;
  }
  // return 0;


}
