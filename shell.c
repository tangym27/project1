#include "shell.h"

/*======== char * trimwhite() ==========
Inputs: char * str
Returns: String with excess whitespace eliminated

Takes a string and removes the excess spaces, then
returns the string.
====================*/
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

/*======== char * command_line() ==========
Inputs: none
Returns: Array of the command lines args given

Prints shell prompt according to user's computer,
then takes command line arguments from stdin and
returns them in a char array.
====================*/
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

/*======== char * parse_args() ==========
Inputs: char * line
        char * limit
Returns: Array of strings, or tokens, separated
based on delimiters between args

Takes a string, separates tokens based on delimiter
given, then returns an array of those tokens.
====================*/
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

/*======== char * redirect_pipe() ==========
Inputs: char ** args
Returns: 0

Given an array of strings, pipes arg 0,
copies what is in stdout into a char array,
pipes arg 1, copies the char array into input
for arg 1. Returns 0.
====================*/
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
/*======== char * find_redirect() ==========
Inputs: char * args
Returns: Int corresponding to which special
character is present

Takes a string and determines whether piping or
redirection is being requested. Returns 1
if a '|' is present, returns 2 if a '>' is present,
returns 3 if a '<' is present.
====================*/
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

/*======== char * redirect_output() ==========
Inputs: char * line
Returns: void

Takes a string, separates the arguments, runs the
first process and redirects stdout into the given
file. (only works with no spaces in char pointer)
====================*/
void redirect_output(char * line) {
    fflush(stdout);
    int file;
    // printf("line %s\n", line );
    char ** arg = parse_args(line, ">");
    // printf("part1:%s\n",parts[0] );
    // printf("part2:%s\n",parts[1] );

    file = open(arg[1], O_CREAT | O_WRONLY , 0644);
    dup(STDOUT_FILENO);
    dup2(file, STDOUT_FILENO);
    char ** args = parse_args(arg[0], " ");
    //printf("oUTPUT HERE\n" );
    execvp(args[0], args);
    close(file);
}

/*======== char * redirect_input() ==========
Inputs: char * line
Returns: void

Takes a string, separates the arguments, reads the
contents of the given file and redirects them towards
stdin. (not functional)
====================*/
// void redirect_input(char * line) {
//     fflush(stdout);
//     int file;
//     printf("line :%s\n", line );
//     char ** parts = parse_args(line, "<");
//     printf("part1:%s\n",parts[0] );
//     printf("part2:%s\n",parts[1] );
//     file=open(parts[1], O_RDONLY, 0644);
//     dup(STDIN_FILENO);
//     dup2(file, STDIN_FILENO);
//     char ** args = parse_args(parts[0], " ");
//     execvp(args[0], args);
//     close(file);
// }

void redirect_input(char * line) {
  fflush(stdout);

    char ** parts = parse_args(line, "<");
    fflush(stdout);

    int fd = open(parts[1], O_RDONLY);
    dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
  //  printf("i got sshere\n" );
  fflush(stdout);

    char ** args = parse_args(parts[0], " ");
    fflush(stdout);

  //  printf("args[1]%s\n",args[0] );
    execvp(args[0], args);
    close(fd);
}
