#include "adms.h"

void clearn(char *name)
{
size_t ln = strlen(name) - 1;
if (*name && name[ln] == '\n') 
    name[ln] = '\0';
    }
int argcomp(char *argmnt)
/*	5 = Add new flights
  	6 = View summarized information
  	7 = Update seat information
  	8 = Update flight pricing
  	9 = Track flight status
*/
{
int retnum;
if(strcmp("inquire_reservation",argmnt)==0)
retnum = 1;
else if(strcmp("make_reservation",argmnt)==0)
retnum = 2;
else if(strcmp("view_reservation",argmnt)==0)
retnum = 3;
else if(strcmp("cancel_reservation",argmnt)==0)
retnum = 4;
else if(strcmp("add_flight",argmnt)==0)
retnum = 5;
else if(strcmp("view_flight",argmnt)==0)
retnum = 6;
else if(strcmp("update_flight",argmnt)==0)
retnum = 7;
else if(strcmp("remove_flight",argmnt)==0)
retnum = 8;
else if(strcmp("add_airline",argmnt)==0)
retnum = 9;
else if(strcmp("view_airline",argmnt)==0)
retnum = 10;
else if(strcmp("remove_airline",argmnt)==0)
retnum = 11; 
return retnum;
}
char * array_pack(int count, char **new)
/*
Usage:
create an array: char *new_1d_array[4096]
use the function: new_1d_array = array_pack(argc, argv)
*/
{
char * req = (char *) malloc(sizeof(char) * count*100);
strcat(req,new[0]);
for(int i=1;i<count;i++) 
{
strcat(req,",");
strcat(req,new[i]);

}
strcat(req,"\0");
return req;
}
/*
This function goes into server file
*/


char ** array_unpack(int count, char* new)
/*
Usage:
create an array: char new_2d_array[4096]
use the function: new_2d_array = array_pack(argc, packed_array)
*/
{ char temp[30];
char *w_new = new;
int len,mark;
mark=0;
len = strlen(w_new);
strcpy(temp,"\0");
char ** req = (char **) malloc(sizeof(char) * MAXLINE);

for(int i=0;i<count;i++)
{req[i] = (char *) malloc(sizeof(char)*100);
int t=0;
for(int j=mark;j<len;j++)
{
if(w_new[j]==',' || w_new[j]=='\0')
{
mark = j+1;
break;}
req[i][t]=w_new[j];
t++;
}
}
return req;
}

int connection_kind(char *node)
{int retnum;
if(strcmp(node,"customer")==0)
retnum = 1;
else if(strcmp(node,"airline")==0)
retnum = 2;
else if(strcmp(node,"sysadmin")==0)
retnum = 3;	
else
retnum = 0;
return retnum;
}



