#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

char * command_line() {
  char * prompt=(char *)calloc(256,1);
  printf("$ " );
  fgets(prompt,256,stdin);
  prompt[strlen(prompt)-1] = 0;
  return prompt;
}

//
// //parse_args based on space
// char ** parse_args( char * line ){
//   char ** args = malloc(256);
//   char * token;
//   int i = 0;
//   while(token){
//     // Seperate based on spaces between args
//     token = strsep(&line, " ");
//     args[i] = token;
//     i++;
//   }
//   return args;
// }
//
//
// int main(int argc, char *argv[]){
// //  printf("Reading from command line: %s\n",command_line());
//   char * str = "ls -a -l";
//   printf("%s\n",str );
//   char ** arr = parse_args(str);
//   printf("djflkasjdfklasdj\n" );
//   printf("-------------------------------\nTESTING USING EXECVP:\n");
//   //arr[strlen(arr) - 1 ] = NULL;
//   execvp(arr[0],arr);
//   return 0;
// }

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

// To test use this is the command line "ls -a -l"
int main(){
  int status;
  char* str = malloc(50);
  char* str_holder = malloc(50);
  printf("$ ");
  fgets(str_holder,50,stdin);
  int firstborn = fork();
  if (!firstborn){
      for (int j = 1; j < strlen(str_holder)-2; j++){
        // printf("asize%lu\n", strlen(str_holder) );
        str[j-1] = str_holder[j];
        //printf("str is %c, str_holder is %c\n", str[j-1], str_holder[j] );
      }

    printf("-------------------------------\nLooking into string: %s\n", str);

    char ** arr = parse_args(str);
    int i =0;
    while(arr[i]){
  	printf("arr[%d]: %s\n", i, arr[i]);
  	i++;
    }
    printf("-------------------------------\nTESTING USING EXECVP:\n");
    //arr[strlen(arr) - 1 ] = NULL;
    execvp(arr[0],arr);
  }
  else if (firstborn){
    int child_id = wait(&status);
    printf("child id: %d\n", child_id);
    main();
    //
    // while (1){
    //   printf("hi\n");
    //   sleep(1);
    // }

  }

//printf("ended parent\n" );
  }
