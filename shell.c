#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

// Try starting with these restrictions on input:
// To make your life easier, you could require that all items on the command line are to be separated by a single space.
// When parsing the line, it might help to count the number of tokens (individual pieces), before parsing.
// You can restrict the locations and ordering of > and <.
// You can limit piping (|) to a single pipe.

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
    printf("c: '%c' |separator: '%s'\n",  c, separator);
    // if (!strcmp(p,separator)){
    if (c == *separator){
      printf("\tGot it!  c: '%c' |separator: '%s'\n", c, separator);
      count++;
    }
  }
  // char * token;
  // int count = 0;
  // int i = 0;
  // while (line[i]){
    // c = (line + i)[0];
    // p = &c;
    // printf("p : '%s' | c: '%c' |separator: '%s'\n", p, c, separator);
  //   printf("%d\n", strcmp(p, separator));
    // if (!strcmp(p,separator)){
    //   printf("\tGot it! p : '%s' | c: '%c' |separator: '%s'\n", p, c, separator);
    //   count++;
    // }
  //   i++;
  // }
  return count;
}
char ** parse_args( char * line , char * separator, int size ){
  char * curr = line;
  char * token;
  printf("line: %s\n", line);
  printf("size line: %d\n", size);
  char ** pointers = malloc((size + 1) * sizeof(char *)); //allocate memory for 5 pointers (b/c at most 5 args) + make room for NULL
  int i = 0;
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
