#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>

char * command_line() {
  char * prompt=(char *)calloc(256,1);
  printf("$ " );
  fgets(prompt,256,stdin);
  prompt[strlen(prompt)-1] = 0;
  return prompt;
}

char ** parse_args( char * line, char * limit ){
  char ** args = malloc(256);
  char * token;
  int i = 0;
  while(token){
    // Seperate based on spaces between args
    token = strsep(&line, limit);
    args[i] = token;
    i++;
  }
  return args;
}

int find_redirect(char * args){
  if(strstr(args,"|")){
    printf("there is a pipe here\n" );
    return 1;
  }
  /* @here : check for < and >, which will return a different num */
  return 0;
}

int redirect_pipe(char ** args){
    printf("larg[0]: %s\n",args[0] );
    printf("arg[1]: %s\n",args[1] );
    char * input  = args[0];
    char * output = args[1];
    char line[256];
    char cmd[256];

    FILE *read=popen(input,"r");

    while (fgets(line,256,read)) {
      line[sizeof(line)-1] =0;
      strcat(cmd,line);
      // printf("temp: \n%s",temp );
      // printf("s: \n%s",s );
      // printf("----\n" );
    }
    pclose(read);
    FILE *write=popen(output,"w");

    fprintf(write,"%s",cmd); //send s to write
    pclose(write);
    return 0;
}

int main(){
  int status;
  char* str = malloc(50);
  while (1){
  int i = 0;
  str = command_line();
  char ** full_arr = parse_args(str, ";");
  while(full_arr[i]){
    printf("======================\n" );
    printf("full_araaar[%d]: %s\n", i, full_arr[i]);
    int j = 0;
    //CHECKS FOR SPECIAL CHARACTERS: AKA HANDLES PIPING.
    int redirect_num =  find_redirect(full_arr[i]);
    if ( redirect_num ){
        if (redirect_num == 1) { // pipe num is 1
          // SEPARATES LS|WC INTO LS AND WC
          char ** full_arr2 = parse_args(str, "|");
          redirect_pipe(full_arr2);
        }
        /*
        @ here : if redirect_num = blah -> handle other redirection
         */
    }
    else{
      char ** arr = parse_args(full_arr[i] , " ");
      while(arr[j]){
        printf("arr[%d]: %s\n", j, arr[j]);
        j++;
      }
      //printf("changed directory!!\n" );
      if (!strcmp(arr[0], "cd")){
        chdir(arr[1]);
      }
      else if (!strcmp(arr[0], "exit")){
        return 0;
      }
      else{
            // THIS IS THE CHILD PROCESS
            int firstborn = fork();
            if (!firstborn){
                printf("-------------------------------\nTESTING USING EXECVP:\n");
                execvp(arr[0],arr);
                return 0;
            }
            //THIS IS THE PARENT PROCESS
            else {
              int child_id = wait(&status);
            }
          }
        }
    i++;
  }
}
  printf("finished the full_arr\n");
  return 0;
}
