# Maia and MiSHELL (its like maya and miguel haha)
# by Maia Brydon and Michelle Tang 

Features:
	Compiles!
	Forks and executes commands!
	Separates multiple commands on one line!
	Can handle simple pipes!

Attempted:
	

Bugs:
	
	
Files & Function Headers:
shell.c
	Handles everything. It's so shellfish. 
	
	/*======== char * trimwhite() ==========
        Inputs: char * str
        Returns: String with excess whitespace eliminated

        Takes a string and removes the excess spaces, then
        returns the string.
        ====================*/
	
	/*======== char * command_line() ==========
        Inputs: none
        Returns: Array of the command lines args given

        Prints shell prompt according to user's computer,
        then takes command line arguments from stdin and
        returns them in a char array.
        ====================*/
	
	/*======== char * parse_args() ==========
        Inputs: char * line
                char * limit
        Returns: Array of strings, or tokens, separated
        based on delimiters between args

        Takes a string, separates tokens based on delimiter
        given, then returns an array of those tokens.
        ====================*/
	
        /*======== char * special() ==========
        Inputs: char * args
        Returns: Int corresponding to which special
        character is present

        Takes a string and determines whether piping or
        redirection is being requested. Returns 1
	if a '|' is present, returns 2 if a '>' is present,
        returns 3 if a '<' is present.
        ====================*/
	
	/*======== char * redirect_pipe() ==========
        Inputs: char ** args
        Returns: 0

        Given an array of strings, pipes arg 0,
        copies what is in stdout into a char array,
        pipes arg 1, copies the char array into input
        for arg 1. Returns 0.
        ====================*/
	
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
