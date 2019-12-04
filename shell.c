// #include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <errno.h>
#include <unistd.h>
// #include <sys/stat.h>
// #include <time.h>
// #include <dirent.h>

// Try starting with these restrictions on input:
// To make your life easier, you could require that all items on the command line are to be separated by a single space.
// When parsing the line, it might help to count the number of tokens (individual pieces), before parsing.
// You can restrict the locations and ordering of > and <.
// You can limit piping (|) to a single pipe.

int count_tokens( char * line ){
  char * curr = line;
  char * token;
  int count = -1; // because the command doesn't count as an argument
  while (curr){
    count++;
    token = strsep(&curr, " ");
  }
  return count;
}
char ** parse_args( char * line ){
  int size = count_tokens(line);
  char * curr = line;
  char * token;
  char ** pointers = malloc(size * sizeof(char *)); //allocate memory for 5 pointers (b/c at most 5 args)
  int i = 0;
  while (curr){
    pointers[i] = malloc(strlen(line)+1);    // allocate desired memory to each pointer
    token = strsep(&curr, " ");
    // Returns the beginning of the original string,
    // sets source to the string starting at 1 index past the location of the new NULL
    pointers[i] = token;
    // printf("iteration %d | curr: %s | token: %s\n", i, curr, token);
    i++;
  }
  return pointers;
}

int main(){
  // char * line = strdup("ls -a -l");
  // printf("Testing parse_args (run 'ls -a -l'):\n");
  // char ** args = parse_args( line );
  // execvp(args[0], args);

  // 5 args (max)
  char * line = strdup("ls -a -l -r");
  printf("Testing parse_args (run ls -a -l -r)\n");
  char ** args = parse_args( line );
  execvp(args[0], args);
  return 0;
}
