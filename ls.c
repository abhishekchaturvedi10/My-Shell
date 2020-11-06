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
	
    		strcat(cwdir,"ls.txt");

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

    void nameFile(struct dirent* name,char* followup)
	{
    	if(name->d_type == DT_REG)        
    	{
        	printf("%s    ",name->d_name);
    	}
    	else if(name->d_type == DT_DIR)   
    	{
        	printf("%s    ",name->d_name);
    	}
    	else                             
    	{
        	printf("%s    ",name->d_name);
    	}
	}

    if(args[1] != NULL && strcmp(args[1],"-1") == 0){

        int i=0;
    	struct dirent **listr;

    	int listn = scandir(".", &listr, 0, alphasort);

    	if (listn >= 0)
    	{
        	for(i = 0; i < listn; i++ )
        	{
            	if(strcmp(listr[i]->d_name,".")==0 || strcmp(listr[i]->d_name,"..")==0)
            	{
                	continue;
            	}
            	else nameFile(listr[i]," ");
            	printf("\n");
        	}
    	}
    	else
    	{
        	perror ("+--- Error in ls ");
    	}

        return 0;
    }

    int i=0;
    struct dirent **listr;

    int listn = scandir(".", &listr, 0, alphasort);

    if (listn >= 0)
    {
        for(i = 0; i < listn; i++ )
        {
            if(strcmp(listr[i]->d_name,".")==0 || strcmp(listr[i]->d_name,"..")==0)
            {
                continue;
            }
            else nameFile(listr[i],"    ");
            if(i%8==0) printf("\n");
        }
        printf("\n");
    }
    else
    {
        perror ("+--- Error in ls ");
    }

    return 0;
}