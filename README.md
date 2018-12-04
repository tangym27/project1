# Maia and MiSHELL (its like maya and miguel haha)
# by Maia Brydon and Michelle Tang 

Features:
* Compiles!
* Forks and executes commands!
* Separates multiple commands on one line!
* Can handle simple pipes!

Attempted:
* Could not get redirection from file to stdin (<) to work

Bugs:
* Redirection from stdout to file (>) only works when arg is given with no spaces (ie. w>foo)
	
Files & Function Headers:

#### shell.c
	Handles a lot of things. It's so shellfish. 
	
	/*======== char * trimwhite() ==========
	
        Header: char * trim_white(char * str)
        Inputs: char * str
        Returns: String with excess whitespace eliminated

        Takes a string and removes the excess spaces (front and back), then
        returns the string.
        ====================*/
	
	/*======== char * command_line() ==========
        Header: char * command_line();
        Inputs: none
        Returns: String of the command lines args given

        Prints shell prompt according to user's computer,
        then takes command line arguments from stdin and
        returns them in a char array.
        ====================*/
	
	/*======== char ** parse_args() ==========
        Header: char ** parse_args( char * line, char * limit );
        Inputs: char * line
                char * limit
        Returns: Array of strings, or tokens, separated
        based on delimiters between args

        Takes a string, separates tokens based on delimiter
        given, then returns an array of those tokens.
        ====================*/
	
        /*======== int find_redirect() ==========
        Header: int find_redirect(char * args);
        Inputs: char * args
        Returns: Int corresponding to which special
        character is present

        Takes a string and determines whether piping or
        redirection is being requested. Returns 1
        if a '|' is present, returns 2 if a '>' is present,
        returns 3 if a '<' is present.
        ====================*/
	
	/*======== int * redirect_pipe() ==========
        Header: int redirect_pipe(char ** args);
        Inputs: char ** args
        Returns: 0

        Given an array of strings, pipes arg 0,
        copies what is in stdout into a char array,
        pipes arg 1, copies the char array into input
        for arg 1. Returns 0.
        ====================*/
	
	/*======== int * redirect_stdout() ==========
        Header: int redirect_input(char * line);
        Inputs: char * line
        Returns: 0

        Given a command, it will separate the string into
        two arrays, what is before and after the '>'. 
        It will then direct the output of the first array
        into the second array.
        ====================*/
	
	/*======== int * redirect_stdin() ==========
        Header: int redirect_output(char * line);
        Inputs: char * line
        Returns: 0

        Given a command, it will separate the string into
        two arrays, what is before and after the '<'. 
        It will then run the first array from the results 
        of the second array. (not functional)
        ====================*/
	
#### main.c

	/*======== char * main() ==========
	Header: int main();
        Inputs: none
        Returns: 0 (if exited)

        Parses the command line args with ';' as a delimiter,
        trims whitespace, checks if redirection or piping is
        needed, checks if arg given is cd or exit, then forks
        off a child process, runs it, and returns to the parent.
        Repeats until all command line arguments have been
        addressed, then proceeds to print out the command prompt.
        ====================*/
