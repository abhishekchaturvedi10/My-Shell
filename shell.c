#include <stdio.h>    
#include <unistd.h>     
#include <stdlib.h> 
#include <string.h>   
#include <sys/wait.h>  
#include <dirent.h>    
#include <sys/types.h>  
#include <fcntl.h>      
#include <ctype.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <time.h>

int cnt = 1;

char cwdir[1000];

char *built_in_str[] = {
    "cd",
    "exit",
    "pwd",
    "history",
    "echo",
    "ls",
    "rm",
    "mkdir",
    "cat",
    "date"
};

int num_built_in = sizeof(built_in_str) / sizeof(char *);

void my_cd(char *args[])
{
    if(args[1] != NULL && strcmp(args[1], "--help") == 0){
	
	getcwd(cwdir,sizeof(cwdir));

	strcat(cwdir,"/");
	
	strcat(cwdir,"cd.txt");
	
        FILE *fp = fopen(cwdir, "r");

        if(!fp) perror("fopen");

        char ch;

        while((ch = fgetc(fp)) != EOF)
            printf("%c", ch);

        printf("\n");

        fclose(fp);

        return;
    }

    if( args[1] != NULL && (strcmp(args[1], "~") == 0  || strcmp(args[1],"/home") == 0)){
        chdir("/home");
    }
    else{

        int x = chdir( args[1] );

        if (x  == -1 ){
            printf("Directory does not exist!\n");
        }
    }
}

void my_exit (char *args[])
{   
    if( args[1] != NULL && strcmp(args[1], "--help") == 0 ){
        printf("exit: exit [n]\n Exit the shell.\n\n\nExits the shell with a status of N.  If N is omitted, the exit status\nis that of the last command executed.\n");
    }
    else{
        exit(0);
    }
}

void my_pwd(char* args[])
{
    if(args[1]!=NULL && strcmp(args[1],"--help")==0){

        getcwd(cwdir,sizeof(cwdir));

	strcat(cwdir,"/");
	
	strcat(cwdir,"pwd.txt");
	
        FILE *fp = fopen(cwdir, "r");

        if(!fp) perror("fopen");

        char ch;

        while((ch = fgetc(fp)) != EOF)
            printf("%c", ch);

        fclose(fp);

        printf("\n");

        return;
    }
    
    char cwd[1024];
    
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}

void my_history(char* args[])
{
    getcwd(cwdir,sizeof(cwdir));

    strcat(cwdir,"/");
	
    strcat(cwdir,"historyList.txt");
	
    FILE *filePointer= fopen(cwdir, "r"); 

    if(filePointer == NULL){
            
        filePointer = fopen(cwdir, "w");

        printf("Empty!\n");

        return;
    }

    if(args[1] != NULL && strcmp(args[1],"-c") == 0){

        FILE *filePointer ;

        filePointer = fopen(cwdir, "w") ;

        fclose(filePointer) ;

        cnt = 1;

        return;
    }
    if(args[1] != NULL && strcmp(args[1],"--help") == 0 ){

        printf("history: history [-c] [-d offset] [n] or history -anrw [filename] or history -ps arg [arg...]\n\tDisplay or manipulate the history list.\n\tDisplay the history list with line numbers, prefixing each modified\n\tentry with a `*'.\n\n\tOptions:\n  -c\t  clear the history list by deleting all of the entries\n  -d\t  offset delete the history entry at position OFFSET. Negative\n\t  offsets count back from the end of the history list\n\n  -a\t  append history lines from this session to the history file\n  -n\t  read all history lines not already read from the history file\nand append them to the history list\n  -r\t  read the history file and append the contents to the history\n\nlist\n  -w\t  write the current history to the history file\n\n  -p\t  perform history expansion on each ARG and display the result\n\t  without storing it in the history list\n  -s\t  append the ARGs to the history list as a single entry\n\n\tIf FILENAME is given, it is used as the history file.\tOtherwise,\n\tif HISTFILE has a value, that is used, else ~/.bash_history.\n\n\tIf the HISTTIMEFORMAT variable is set and not null, its value is used\n\tas a format string for strftime(3) to print the time stamp associated\n\twith each displayed history entry.\tNo time stamps are printed otherwise.\n\n\tExit Status:\n\tReturns success unless an invalid option is given or an error occurs.\n");
        
        return;
    }

    char dataToBeRead[64];

    while( fgets ( dataToBeRead, 64, filePointer ) != NULL ) 
    { 
        printf( "%s" , dataToBeRead ) ; 
    } 
          
    fclose(filePointer) ;

} 

void my_echo(char *args[])
{
    char line[64]; 

    if ( args[1] != NULL && strcmp( args[1], "-n" ) == 0 )
    {
        int k = 0;

        for(int i = 2 ; args[i] != NULL ; i++){

            int j = 0; 

            while( args[i][j] != '\0' ){

                line[k++] = args[i][j++];
            }

            line[k++] = ' ';
        }

        char temp[64];

        int j=0, i;

        for(i=1;i<strlen(line)-2;i++){

            temp[j++]=line[i];
        }

        printf("%s", temp);

        return;
    }

    if (args[1]!=NULL && strcmp(args[1], "--help") == 0)
    {
        
        getcwd(cwdir,sizeof(cwdir));

    strcat(cwdir,"/");
	
    strcat(cwdir,"echo.txt");
	
    FILE *filePointer= fopen(cwdir, "r");

        if(!fp) perror("fopen");

        char ch;

        while((ch = fgetc(fp)) != EOF)
            printf("%c", ch);

        fclose(fp);

        return;
    }  

    for(int i = 1 ; args[i] != NULL ; i++)
        printf("%s ", args[i]);

    printf("\n");
}

int check_built_in_command(char *args[])
{
    int i;
    
    if ( args[0] == NULL ) {
        return 0;
    }
    
    for (i=0; i < num_built_in; i++) {
        if (strcmp(args[0], built_in_str[i]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

void execute_built_in_command(char *args[])
{   
    if (strcmp(args[0], built_in_str[0]) == 0) {
        my_cd(args);
    }
    
    else if (strcmp(args[0], built_in_str[1]) == 0) {
        my_exit(args);
    }
    
    else if (strcmp(args[0], built_in_str[2]) == 0) {
        my_pwd(args);
    }
    
    else if (strcmp(args[0], built_in_str[3]) == 0) {
        my_history(args);
    }

    else if(strcmp(args[0], built_in_str[4]) == 0) {
        my_echo(args);
    }

    else if(strcmp(args[0], built_in_str[5]) == 0) {

        int p = fork();

        if(p>0){
            wait(NULL);
        }
        else if(p==0){
		
	    getcwd(cwdir,sizeof(cwdir));

    	strcat(cwdir,"/");
	
    	strcat(cwdir,ls);

            if (execv(cwdir, args) < 0) { 
                printf("\nCould not execute command..\n"); 
            }
        }
        else{
            printf("\nFailed forking child...\n"); 
        }
    }

    else if(strcmp(args[0], built_in_str[6]) == 0) {

        int p = fork();

        if(p>0){
            wait(NULL);
        }
        else if(p==0){
	
	getcwd(cwdir,sizeof(cwdir));

    	strcat(cwdir,"/");
	
    	strcat(cwdir,rm);

            if (execv(cwdir, args) < 0) { 
                printf("\nCould not execute command..\n"); 
            }
        }
        else{
            printf("\nFailed forking child...\n"); 
        }
    }

    else if(strcmp(args[0], built_in_str[7]) == 0) {
        
        int p = fork();

        if(p>0){
            wait(NULL);
        }
        else if(p==0){
		
		getcwd(cwdir,sizeof(cwdir));

    		strcat(cwdir,"/");
	
    		strcat(cwdir,mkdir);            

            if (execv(cwdir, args) < 0) { 
                printf("\nCould not execute command..\n"); 
            }
        }
        else{
            printf("\nFailed forking child...\n"); 
        }
    }

    else if(strcmp(args[0], built_in_str[8]) == 0) {
        
        int p = fork();

        if(p>0){
            wait(NULL);
        }
        else if(p==0){

		getcwd(cwdir,sizeof(cwdir));

    	strcat(cwdir,"/");
	
    	strcat(cwdir,cat);

            if (execv(cwdir, args) < 0) { 
                printf("\nCould not execute command..\n"); 
            }
        }
        else{
            printf("\nFailed forking child...\n"); 
        }
    }

    else if(strcmp(args[0], built_in_str[9]) == 0) {
        
        int p = fork();

        if(p>0){
            wait(NULL);
        }
        else if(p==0){

		getcwd(cwdir,sizeof(cwdir));

    	strcat(cwdir,"/");
	
    	strcat(cwdir,date);

            if (execv(cwdir, args) < 0) { 
                printf("\nCould not execute command..\n"); 
            }
        }
        else{
            printf("\nFailed forking child...\n"); 
        }
    }

    else {
    	printf("Unrecognized command from here!\n");
    }
}

char **parse_command(char *my_line)
{
    int buffer_size = 64;
    int i = 0;
    char *arg;
    char **args = malloc(buffer_size * sizeof(char*));
    
    arg = strtok(my_line, " \t\r\n\a");

    while (arg != NULL) {
        args[i] = arg;
        i++;
        arg = strtok(NULL, " \t\r\n\a");
    }
    
    args[i] = NULL;
    
    return args;
}

char *read_command_line(void)
{
    int bufsize = 128;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;
    int i = 0;
    
    while ( c != '\n' ) {
        c = getchar();
        buffer[i] = c;
        i++;
    }
    
    return buffer;
}

void print_prompt()
{
    printf(">>> $ ");
}

int main(int argc, char *args[])
{
    char *my_line;
    char **my_command;
    
    getcwd(cwdir,sizeof(cwdir));

    strcat(cwdir,"/");
	
    strcat(cwdir,"historyList.txt");
	
    FILE *filePointer= fopen(cwdir, "r"); 

    if(!filePointer) {
        filePointer = fopen(cwdir, "w") ;
    }

    if(!filePointer) {

        perror("fopen");
        exit(1);
    }

    char dataToBeRead[64];

    while(filePointer != NULL && fgets ( dataToBeRead, 64, filePointer ) != NULL ) 
    { 
        cnt++;
    } 
          
    fclose(filePointer) ; 

    while(1)
    {
        print_prompt();

        my_line = read_command_line();
        my_command = parse_command(my_line);
        
        if (my_command[0] != NULL) {

            filePointer = fopen(cwdir, "a") ; 
      
            if ( filePointer == NULL ) 
            {    
                perror("fopen");
            } 
            else
            {
                fprintf(filePointer, "%d %s\n", cnt++, my_line);
          
                fclose(filePointer) ; 
            }

            if (check_built_in_command(my_command) ) {

                execute_built_in_command(my_command);
            }
            else {
                printf("%s\n", "Unrecognized commands");
            }
        }
    }
    
    return 0;
}