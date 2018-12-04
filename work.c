#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>
#include <pwd.h>

char * trim_white(char * str) {
  while (*str==' ') {
    str++;
  }
  int i = strlen(str)-1;
  for (; i > 1 ; i--){
    if (str[i]==' ' || str[i] == '\n' ){
      str[i] = 0;
    }
    else {
      break;
    }
}
  return str;
}

char * command_line() {
  char *host = malloc(256);
  gethostname(host, 255);
  struct passwd *user = getpwuid(getuid());

  char * prompt=(char *)calloc(256,1);
  printf("(M&M) %s: %s $ ", host, user->pw_name);
  fflush(stdout);
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

int redirect_pipe(char ** args){
  //  printf("larg[0]: %s\n",args[0] );
  //  printf("arg[1]: %s\n",args[1] );
    char * input  = args[0];
    char * output = args[1];
    char line[256];
    char cmd[256];

    FILE *read=popen(input,"r");

    while (fgets(line,256,read)) {
      line[sizeof(line)-1] =0;
      strcat(cmd,line);
    }
    pclose(read);
    FILE *write=popen(output,"w");

    fprintf(write,"%s",cmd); //send s to write
    pclose(write);
    return 0;
}

int find_redirect(char * args){
  if(strstr(args,"|")){
    printf("there is a pipe here\n" );
    return 1;
  }
  if(strstr(args,">")){
    printf("redirecting stdout to file\n");
    return 2;
  }
  if(strstr(args,"<")){
    printf("redirecting file to stdin\n");
    return 3;
  }
  return 0;
}

void redirect_input(char * line) {
    fflush(stdout);
    // printf("line %s\n", line );
    char ** parts = parse_args(line, ">");
    // printf("part1:%s\n",parts[0] );
    // printf("part2:%s\n",parts[1] );

    int fd = open(parts[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    char ** args = parse_args(parts[0], " ");
    //printf("oUTPUT HERE\n" );
    execvp(args[0], args);
    close(fd);
}

void redirect_output(char * line) {
    fflush(stdout);
    printf("line :%s\n", line );
    char ** parts = parse_args(line, "<");
    printf("part1:%s\n",parts[0] );
    printf("part2:%s\n",parts[1] );
    int fd=open(parts[1],O_CREAT | O_RDWR,0644);
    dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    char ** args = parse_args(parts[0], " ");
    execvp(args[0], args);
    close(fd);
}

int main(){
  int status;
  char* str = malloc(50);
  while (1){
  int i = 0;
  str = command_line();
  char ** full_arr = parse_args(str, ";");
  while(full_arr[i]){
   fflush(stdout);
   full_arr[i] = trim_white(full_arr[i]);
  //printf("full_arr: %s\n", full_arr[i] );
    int j = 0;
    int redirect_num =  find_redirect(full_arr[i]);
    if (redirect_num == 1) { // pipe num is 1
          // SEPARATES LS|WC INTO LS AND WC
          char ** full_arr2 = parse_args(str, "|");
          redirect_pipe(full_arr2);
    }
    else{
    //  printf("oh no \n" );
      char ** arr = parse_args(full_arr[i] , " ");

      // while(arr[j]){
      //   //printf("arr[%d]: %s\n", j, arr[j]);
      //   j++;
      // }
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
              //  printf("-------------------------------\nTESTING USING EXECVP:\n");
              if (redirect_num == 2){
                redirect_output(arr[i]);
              }
              else if (redirect_num == 3){
                printf("burps\n" );
                redirect_input(arr[i]);
              }
              else{
                //arr = parse_args(full_arr[i] , " ");
                execvp(arr[0],arr);
                return 0;
              }
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
  //printf("finished the full_arr\n");
  return 0;
}
