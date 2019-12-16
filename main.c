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
#include <pwd.h>
#include "shell.h"

int main(){

  char line[200];
  char path[200];
  // char * separator;
  char ** args;
  char ** semiargs;
  char ** pipeargs;
  // separator = " ";
  printf("Hello there! Welcome to my shell :)\n");
  while (1){
    printf("shell $: ");
    fgets(line, 200, stdin); //adds a newline to the end of line
    line[strlen(line) - 1] = '\0';
    // printf("\tParsing with ';'...\n");
    // parse using ;
    semiargs = parse_args(line, ";", count_tokens(line, ";"));
    int i = 0;
    // printf("\tParsing with ' '...\n");
    while (semiargs[i]){
      // printf("\t\tParsing semiargs[%d]...\n", i);
      args = parse_args(semiargs[i], " ", count_tokens(semiargs[i], " ")); //parses based on spaces
      pipeargs = parse_args(semiargs[i], "|");
      if (pipeargs[1]){
        pipeit(pipeargs);
      }
      // printf("\t\tRunning args from semiargs[%d]...\n", i);
      execArgs(args);
      i++;
    }
  }
  return 0;


}
