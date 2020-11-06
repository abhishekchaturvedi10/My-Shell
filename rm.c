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

void main(int argc, char* args[])
{
	if(strcmp(args[0],"rm")==0 )
    {
        char* buff=(char*)malloc(sizeof(char)*256);
        char* dirr=(char*)malloc(sizeof(char)*1000);
        char* buff1=(char*)malloc(sizeof(char)*256);

        buff=getcwd(NULL,0);
        int len=strlen(buff),i,ii=2;
        
        for(i=0;i<len;i++)
            buff1[i]=buff[i];
        buff1[len]='\0';        
        DIR* dir=opendir(buff);
        struct dirent* c;
        int x=0;
        if(args[1][0]=='-'&&args[1][1]=='r'&&args[1][2]=='\0')
        {
            if(dir)
            {
                while((c=readdir(dir))!=NULL){
                    dirr=c->d_name;
                    ii=2;
                    while(args[ii]!=NULL)  
                    if(strcmp(dirr,".")!=0&&strcmp(dirr,"..")!=0&&strcmp(dirr,args[ii])==0)
                    {
                        buff1=strcat(buff1,"/");
                        buff1=strcat(buff1,dirr);
                        remove(buff1);
                        x++;
                        for(i=0;i<len;i++)
                            buff1[i]=buff[i];
                        buff1[len]='\0';        
                        break;
                    }
                    else
                        ii++;
                }
            }
            else{

                printf("Directory error!\n");
                exit(1);
            }
        }
        else if(args[1][0]=='-'&&args[1][1]=='v'&&args[1][2]=='\0')
        {
            if(dir)
            {
                while((c=readdir(dir))!=NULL){
                    dirr=c->d_name;
                    ii=2;
                    while(args[ii]!=NULL) {
                    if(strcmp(dirr,".")!=0&&strcmp(dirr,"..")!=0&&strcmp(dirr,args[ii])==0&&c->d_type != DT_DIR)
                    {
                        buff1=strcat(buff1,"/");
                        buff1=strcat(buff1,dirr);
                        remove(buff1);
                        x++;
                        printf("File %s is removed\n",args[ii]);
                        for(i=0;i<len;i++)
                            buff1[i]=buff[i];
                        buff1[len]='\0';        
                        break;
                    }
                    else
                        ii++;
                    }
                }
            }
            else{
                
                printf("Directory error!\n");
                exit(1);
            }

            if(x!=0)
                printf("In total %d files were removed\n",x);
            else
                printf("No files were removed\n");
        }
        else if(args[1] != NULL && strcmp(args[1],"--help")==0){
        	
        	getcwd(cwdir,sizeof(cwdir));

    		strcat(cwdir,"/");
	
    		strcat(cwdir,"rm.txt");

		FILE *fp = fopen(cwdir, "r");

        	if(!fp) perror("fopen");

        	char ch;

        	while((ch = fgetc(fp)) != EOF)
            	printf("%c", ch);

        	fclose(fp);

        	return ;
        }
        else
        {
            printf("Unrecognized command!\n");
        }
        
        x=0;
        closedir(dir);
    }
}