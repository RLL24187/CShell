// #include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <errno.h>
#include <unistd.h>
// #include <sys/stat.h>
// #include <time.h>
// #include <dirent.h>

int main(){

  char * line = strdup("ls -a -l");

  printf("Testing parse_args (run 'ls -a -l'):\n");

  char ** args = parse_args( line );

  execvp(args[0], args);



  // 5 args (max)

  // char * line = strdup("ls -a -l -r");
  //
  // printf("Testing parse_args (run ls -a -l -r)\n");
  //
  // char ** args = parse_args( line );
  //
  // execvp(args[0], args);

  return 0;

}
