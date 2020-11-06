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

	if(args[1]!=NULL && strcmp(args[1],"--help") ==0){

		getcwd(cwdir,sizeof(cwdir));

    		strcat(cwdir,"/");
	
    		strcat(cwdir,"cat.txt");

		FILE *fp = fopen(cwdir, "r");

        if(!fp) {

            perror("fopen");
            exit(1);
        }

        char ch;

        while((ch = fgetc(fp)) != EOF)
            printf("%c", ch);

        fclose(fp);

		return 0;
	}

	if(args[1]!=NULL && strcmp(args[1],"-n")==0){

		int i=0;
    	struct dirent **listr;
	
	getcwd(cwdir,sizeof(cwdir));

    	int listn = scandir(cwdir, &listr, 0, alphasort);

    	if (listn >= 0)
    	{
        	for(i = 0; i < listn; i++ )
        	{
            	if(strcmp(listr[i]->d_name,args[2])==0)
            	{
               		char filename[256];

        			sprintf(filename, "%s", listr[i]->d_name);

        			getcwd(cwdir,sizeof(cwdir));

        			strcat(cwdir, filename);

        			FILE *fp = fopen(cwdir, "r");

        			if(!fp) perror("fopen");

        			char line[64];

        			int lineNo = 1;

    				while (fgets(line, sizeof(line), fp)) {
        				printf("%d %s", lineNo++, line); 
    				}

        			fclose(fp);

                    printf("\n");

        			return 0;
            	}
        	}

            printf("File does not exist!\n");
    	}
    	else
    	{
        	perror ("+--- Error in ls ");
    	}

    	return 0;
	}

	int i=0;
    struct dirent **listr;
	
    getcwd(cwdir,sizeof(cwdir));

    int listn = scandir(cwdir, &listr, 0, alphasort);

    if (listn >= 0)
    {
        for(i = 0; i < listn; i++ )
        {
            if(strcmp(listr[i]->d_name,args[1])==0)
            {
                char filename[256];

        		sprintf(filename, "%s", listr[i]->d_name);

        		getcwd(cwdir,sizeof(cwdir));

        		strcat(cwdir, filename);

        		FILE *fp = fopen(cwdir, "r");

        		if(!fp) perror("fopen");

        		char ch;

        		while((ch = fgetc(fp)) != EOF)
            		printf("%c", ch);

        		fclose(fp);

        		return 0;
            }
        }

        printf("File does not exist!\n");
    }
    else
    {
        perror ("+--- Error in ls ");
    }

    printf("Unrecognized command!\n");

    return 0;
}
