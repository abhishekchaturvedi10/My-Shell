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

char cwdir[1000];

int main(int argc, char* args[]){

	if(args[1] != NULL && strcmp(args[1],"--help") == 0){

		getcwd(cwdir,sizeof(cwdir));

    		strcat(cwdir,"/");
	
    		strcat(cwdir,"mkdir.txt");

		FILE *fp = fopen(cwdir, "r");

        if(!fp) {
            perror("fopen");
            exit(1);
        }

        char ch;

        while((ch = fgetc(fp)) != EOF){
            
            printf("%c", ch);
        }

        fclose(fp);

        return 0;
	}

	if(args[1] != NULL && strcmp(args[1],"-v") == 0){

		int stat = mkdir(args[2], 0777);

		if(stat==-1)
    	{
        	perror("+--- Error in mkdir \n");

        	return 0;
    	}
		
		printf("mkdir: created directory %s\n", args[2]);	

		return 0;
    }

    int stat = mkdir(args[1], 0777);

    if(stat==-1)
    {
        perror("+--- Error in mkdir \n");
    }

    return 0;
}