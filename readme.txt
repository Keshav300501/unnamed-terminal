Commands to be implemented:

Internal Commands:
    cd
        Changes directory to as specified.
    echo
        Displays text as specified.
        -n : Does not output trailing line.
    history
        Displays file history.
        -c : Clears history.
        -w : Writes history to specified file.
    pwd
        Displays current directory.
    exit
        Exits shell.

External Commands:
    ls
        Lists file in specified or current directory.
        -a : Lists all files including those starting with '.'.
        -r : Sorts list in reverse order.
    cat
        Displays text from stdout or file as specified.
        -E : Shows $ at the end of each line. 
        -n : Numbers all output lines,
    date
        Shows system date and time.
        -u : Shows UTC time.
    rm 
        Removes files as specified.
        -i : Prompts before every removal.
        -d : Removes empty directories.
    mkdir
        Creates new directories.
        -p : Make parent directories as needed.
        -v : Prints message for each created directory.