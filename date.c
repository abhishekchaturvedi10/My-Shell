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
#include <stdio.h>
#include <time.h>

char cwdir[1000];

int main(int argc, char* args[])
{

  if(args[1]!=NULL && strcmp(args[1],"--help")==0){

    getcwd(cwdir,sizeof(cwdir));

    		strcat(cwdir,"/");
	
    		strcat(cwdir,"date.txt");

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
  if(args[1]!=NULL && strcmp(args[1],"-u")==0){

    struct tm *local;
    time_t t;

    t = time(NULL);
    
    local = gmtime(&t);
    printf("%s", asctime(local));

    return 0;
  } 

  int dayofweek(int d, int m, int y)  
  {  
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };  
    y -= m < 3;  
    return ( y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;  
  } 

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  char month[20], day[20];

  if(dayofweek(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) == 1){
    strcpy(day, "Monday");
  }
  else if(dayofweek(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) == 2){
    strcpy(day, "Tuesday");
  }
  else if(dayofweek(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) == 3){
    strcpy(day, "Wednesday");
  }
  else if(dayofweek(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) == 4){
    strcpy(day, "Thursday");
  }
  else if(dayofweek(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) == 5){
    strcpy(day, "Friday");
  }
  else if(dayofweek(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) == 6){
    strcpy(day, "Saturday");
  }
  else if(dayofweek(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) == 7){
    strcpy(day, "Sunday");
  }

  if(tm.tm_mon + 1 == 1){
    strcpy(month, "January");
  }
  else if(tm.tm_mon + 1 == 2){
    strcpy(month, "Febraury");
  }
  if(tm.tm_mon + 1 == 3){
    strcpy(month, "March");
  }
  if(tm.tm_mon + 1 == 4){
    strcpy(month, "April");
  }
  if(tm.tm_mon + 1 == 5){
    strcpy(month, "May");
  }
  if(tm.tm_mon + 1 == 6){
    strcpy(month, "June");
  }
  if(tm.tm_mon + 1 == 7){
    strcpy(month, "July");
  }
  if(tm.tm_mon + 1 == 8){
    strcpy(month, "August");
  }
  if(tm.tm_mon + 1 == 9){
    strcpy(month, "September");
  }
  if(tm.tm_mon + 1 == 10){
    strcpy(month, "October");
  }
  if(tm.tm_mon + 1 == 11){
    strcpy(month, "November");
  }
  if(tm.tm_mon + 1 == 12){
    strcpy(month, "December");
  }

  printf("%s %d %s %d %02d:%02d:%02d %s\n", day, tm.tm_mday, month, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_zone);

  return 0;
}