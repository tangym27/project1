#include "shell.h"

/*======== char * main() ==========
        Inputs: none
        Returns: 0 (if exited)

        Parses the command line args with ';' as a delimiter,
        trims whitespace, checks if redirection or piping is
        needed, checks if arg given is cd or exit, then forks
        off a child process, runs it, and returns to the parent.
        Repeats until all command line arguments have been
        addressed, then proceeds to print out the command prompt.
====================*/
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
