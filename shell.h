#ifndef HEADER_FILE
#define HEADER_FILE

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

char * trim_white(char * str);
char * command_line();
char ** parse_args( char * line, char * limit );
int special(char * args);
int redirect_pipe(char ** args);
int find_redirect(char * args);
void redirect_input(char * line);
void redirect_output(char * line);

#endif
