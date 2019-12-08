// #include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include "shell.h"

int main(){

  char line[200];
  char path[200];
  char * separator;
  char ** args;
  separator = " ";
  while (1){

    printf("shell $: \n");
    fgets(line, 100, stdin); //adds a newline to the end of line
    if (line[strlen(line) - 2] != '/'){
      line[strlen(line) - 1] = '/';
      line[strlen(line)] = '\0';
    }
    else{
      line[strlen(line) - 1] = '\0';
    }
    args = parse_args(line, separator, count_tokens(line, separator));
    execArgs(args);
  }
  // if (!pid){ //child process
  //
  //   // strcpy(line, "ls -l -a");
  //   printf("Testing parse_args (run '%s'):\n", line);
  //
  //   args = parse_args( line , separator, count_tokens(line, separator));
  //
  //   execvp(args[0], args);
  //   printf("exec failed: %s\n", strerror(errno));
  //   return 0;
  // }
  // else{ //parent process
  //
  //   // strcpy(line, "ls -l -a -r");
  //   printf("Testing parse_args (run '%s')\n", line);
  //
  //   args = parse_args( line , separator, count_tokens(line, separator));
  //
  //   execvp(args[0], args);
  //   printf("exec failed: %s\n", strerror(errno));
  //
  //   return 0;
  // }
  // separator = " ";
  // strcpy(line, "ls -l -a");
  // printf("Testing parse_args (run '%s'):\n", line);
  //
  // args = parse_args( line , separator, count_tokens(line, separator));
  //
  // execvp(args[0], args);
  // printf("exec failed: %s\n", strerror(errno));
  return 0;


}
