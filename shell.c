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

int count_tokens( char * line , char * separator){
  char * p = line;
  // char * token;
  int count = 0;
  int i = 0;
  while (line[i]){
    p = &line[i];
    printf("p or line[i]: '%s', separator: '%s'\n", p, separator);
    if (!strcmp(p,separator)){
      count++;
    }
    i++;
  }
  return count;
}
char ** parse_args( char * line , char * separator, int size ){
  char * curr = line;
  printf("line: %s\n", line);
  char * token;
  char ** pointers = malloc((size + 1) * sizeof(char *)); //allocate memory for 5 pointers (b/c at most 5 args) + make room for NULL
  int i = 0;
  printf("size line: %d\n", size);
  while (curr){
    printf("iteration %d | curr: %s | token: %s\n", i, curr, token);
    // pointers[i] = malloc(strlen(line)+1);    // allocate desired memory to each pointer
    token = strsep(&curr, separator);
    // Returns the beginning of the original string,
    // sets source to the string starting at 1 index past the location of the new NULL
    pointers[i] = token;
    printf("iteration %d | curr: %s | token: %s\n", i, curr, token);
    i++;
  }
  return pointers;
}
