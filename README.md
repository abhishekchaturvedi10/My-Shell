# My-Shell
TASK -

Design your a linux shell that can handle five, internal commands - 'cd', 'echo, 'history', 'pwd' and 'exit'. These commands would be handled directly by the shell. 
Your shell should also be able to handle five external commands - 'ls', 'cat', 'date', 'rm' and 'mkdir'. For these external commands you need to write individual programs to handle these commands. To handle these external commands, the shell should typically create a new process, using the fork() system call and within each process you need to use the execl() family system call to run the individual program. The parent program must also wait for the child program to terminate using the wait() family of system calls.
For each of these commands, you need not handle all the command line options.
