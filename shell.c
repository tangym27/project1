#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


char * command_line() {
  char * prompt=(char *)calloc(256,1);
  printf("$ " );
  fgets(prompt,256,stdin);
  prompt[strlen(prompt)-1] = 0;
  return prompt;
}


int main(int argc, char *argv[]){
  printf("Reading from command line: %s\n",command_line());

}



//parse_args based on space
char ** parse_args( char * line ){
  char ** args = malloc(256);
  char * token;
  int i = 0;
  while(token){
    // Seperate based on spaces between args
    token = strsep(&line, " ");
    args[i] = token;
    i++;
  }
  return args;
}
