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

int change (char * dir){
    char cwd[PATH_MAX+100000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("Current working dir: %s\n", cwd);
      char * dir_holder = malloc(50);
    //  char * dir = malloc(50);
     // printf("Enter in directory you want to look in ie '/..' \n");
    // fgets(dir_holder, 50, stdin);
  //    for (int j = 1; j < strlen(dir_holder)-2; j++){
  //       printf("asize%lu\n", strlen(str_holder) );
  //      dir[j-1] = dir_holder[j];
  //  int success = chdir("/Users/mtang/Documents/Systems/project1/..");
  // }
      strcat(cwd, "/");
      strcat(cwd, dir );
      printf("cwd %s\n", cwd );
      int success = chdir(cwd);
      printf("chdir %d\n", success );
    } else {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}

int shell_exit(){
  printf("we have exited the 'bash'\n" );
  exit(0);
}

int main(){
  int status, astatus;

  char* str = malloc(50);
  while (1){
    int i = 0;
    str = command_line();
    char ** full_arr = parse_args(str, ";");
    while(full_arr[i]){
      printf("======================\n" );
      printf("full_arr[%d]: %s\n", i, full_arr[i]);
      int j = 0;
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
      i++;
    }
  }
  printf("finished the full_arr\n");
  return 0;
}
