To run for the first time, do ./run.sh. If binaries have been already generated, this will just run the binaries.
To clean the binaries and rerun, do ./clean.sh and then ./run.sh. 
Both shell scripts call the makefile and perform the actions accordingly.
The commands have been implemented to have as similar a functionality to the originals as possible.


Commands to be implemented:

Internal Commands:
    cd
        Usage : cd [dir]
        Changes directory to as specified.
    echo
        Usage : echo [-n]
                echo [-n] [STRING] 
        Displays text as specified.
        -n : Does not output trailing line.
    history
        Usage : history [-c]
                history [-c] [-w] [file name]
        Displays file history.
        -c : Clears history.
        -w : Writes history to specified file.
    pwd
        Usage : pwd
        Displays current directory.
    exit
        Usage : exit
        Exits shell.

External Commands:
    ls
        Usage : ls [-a] [-r] [directory name]
        Lists file in specified or current directory.
        -a : Lists all files including those starting with '.'.
        -r : Sorts list in reverse order.
    cat
        Usage : cat [-E] [-n] [file name]
                cat [-E] [-n]
        Displays text from stdout or file as specified. 
        -E : Shows $ at the end of each line. 
        -n : Numbers all output lines,
    date
        Usage : date [-u]
        Shows system date and time.
        -u : Shows UTC time.
    rm 
        Usage : rm [-i] [-d] [file/directory name]
        Removes files as specified.
        -i : Prompts before every removal.
        -d : Removes empty directories.
    mkdir
        Usage : mkdir [-p] [-v] [file name]
        Creates new directories.
        -p : Make parent directories as needed.
        -v : Prints message for each created directory.