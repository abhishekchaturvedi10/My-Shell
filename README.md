# My-Shell
Your task is to design your a simple shell that can handle five, internal com-
mands - `cd', `echo', `history', `pwd' and `exit'. These commands
would be handled directly by the shell. Your shell should also be able to han-
dle five external commands - `ls', `cat', `date', `rm' and `mkdir'. For
these external commands you need to write individual programs to handle these
commands. To handle these external commands, the shell should typically cre-
ate a new process, using the fork() system call and within each process you
need to use the execl() family system call to run the individual program. The
parent program must also wait for the child program to terminate using the
wait() family of system calls.
For each of these commands, you need not handle all the command line
options. Two options per command is sufficient.
