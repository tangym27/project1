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

// To test use this is the command line "ls -a -l"
int main(){
//  change("dir");
  int status, astatus;
  char* str = malloc(50);
  char* str_holder = malloc(50);
  printf("$ ");
  fgets(str_holder,50,stdin);
 // printf("this is str_holder %d\n", strncmp(str_holder, "exit", 3) );
 // int i;
 // for (i  = 0; i < strlen(str_holder); i++){
 //   printf("str_holder[%d]: %s"), i , str_holder[i]);
 // }
 // printf("this is str_holder2 %d\n", strncmp("exit", "exit", 3) );
 //
 // printf("strcmp%d\n",strncmp(str_holder, "exit", 4) );
 // if (!strcmp(str_holder, "exit")){
 //    shell_exit();
 // }
  int firstborn = fork();
  if (!firstborn){ // child process
      for (int j = 1; j < strlen(str_holder)-1; j++){
        str[j-1] = str_holder[j];
      }
      str[strlen(str) - 1 ] = 0;
      printf("-------------------------------\nLooking into string: %s\n", str);
      char ** full_arr = parse_args(str, ";");
      int i =0;
      while(full_arr[i]){
        int j = 0;
        printf("full_arr[%d]: %s\n", i, full_arr[i]);
        char ** arr = parse_args(full_arr[i] , " ");
        while(arr[j]){
          printf("arr[%d]: %s\n", j, arr[j]);
          j++;
        }
        printf("-------------------------------\nTESTING USING EXECVP:\n");
        int a =fork();
        if (!a){
          if (!strcmp(arr[0],"cd")){
            printf("hey there its a cd \n" );
            printf("arr[1]:%s\n", arr[1] );
            change(arr[1]);
          }
          else{
          execvp(arr[0],arr);
        }
        }
        else if (a){
          wait(&astatus);
          i++;
      }
      }
      //arr[strlen(arr) - 1 ] = NULL;
    }
else if (firstborn){
  int child_id = wait(&status);
  main();
  // while (1){
  //   printf("hi\n");
  //   sleep(1);
  // }

}

  }
