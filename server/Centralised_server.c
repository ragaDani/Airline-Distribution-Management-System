#include "../headers/adms.h"

pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;
void *centreserver(void *args)
{ struct db_intr *sqlobj;
int trx =1, option;
char *ptr;
char trxstr[1];
sqlobj = (struct db_intr*) args;
char ack[] = {"ack"};
 int connfd=sqlobj->connfd;
 char buffer[MAXLINE],query[MAXLINE], sendline[MAXLINE], dest[MAXLINE];
 int connectorid;
 char username[50], password[50], container[50],message[MAXLINE];
 char temp[10];
 MYSQL *conn = sqlobj->conn;
 MYSQL_RES *res;
 MYSQL_ROW row;
 char *buffern = (char*)malloc(sizeof(char)*MAXLINE);
 int price,seats,flightid,airlineid,customerid,reservationid,num_fields;
 char **weavestr = malloc(sizeof(char)*MAXLINE);
 for(int i=0;i<9;i++)
 {
 weavestr[i] = malloc(sizeof(char)*20);
 }
  // Receiving kind of client
 read(connfd,buffer,MAXLINE);
 printf("Connection at %d identified as %s\n",connfd,buffer);
 connectorid = connection_kind(buffer);
 acknowledge;
 printf("Connectorid is %d\n",connectorid);
 memset(buffer,0,MAXLINE);
 switch(connectorid)
 /* connectorid:
 Customer = 1
 Airline = 2
 System Administrator = 3
 */
 {
 case 1: //CUSTOMER BEGINS
 while(trx)
 {
 /*read(connfd,buffer,MAXLINE);
 strcpy(username,buffer);
 strcpy(buffer,"\0");
 acknowledge;
 read(connfd,buffer,MAXLINE);
 strcpy(password,buffer);
 strcpy(buffer,"\0");
 
 snprintf(query,MAXLINE,"SELECT loginid from ADMS_Users where UserName='%s AND Password=MD5('%s')",username,password);
    if(mysql_query(conn,query)<0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("%llu user authenticated\n",mysql_affected_rows(conn));
    if(mysql_affected_rows(conn)>0)
         write(connfd,"1",strlen("1"));
    else
        write(connfd,"0",strlen("0"));
*/read(connfd,buffer,MAXLINE);
  acknowledge;
  strcpy(container,buffer);
  option = argcomp(container);
  memset(buffer,0,MAXLINE);
  switch(option)
  {
  case 1: // ENQUIRE_RESERVATION
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(3,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
snprintf(query,MAXLINE,"select * from Flight where to_location='%s' AND from_location='%s'",weavestr[1],weavestr[2]);

          printf("DB query made: %s\n",query);
          //pthread_mutex_lock(&mlock); //thread locked
          mysql_query(conn,query);
          res = mysql_use_result(conn);
          num_fields=mysql_num_fields(res);
          
          while ((row = mysql_fetch_row(res)) != NULL)
          {
              for(int i=0;i<num_fields;i++)
              {
                  printf("%s ", row[i] ? row[i] : "NULL");
                  sprintf(sendline,"%s ", row[i] ? row[i] : "NULL");
                  strcat(dest,sendline);
              }
              printf("\n");
              strcat(dest,"\n");
          }
          mysql_free_result(res);
           //pthread_mutex_unlock(&mlock); //thread unlocked
          strcpy(message,dest);
          write(connfd,message,strlen(message));
          read(connfd,trxstr,1);
          trx = atoi(trxstr);
          acknowledge;
 break; // ENQUIRE_RESERVATION ENDS
 case 2: // GET_INFO
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(7,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
strcpy(temp,weavestr[1]);
customerid = atoi(temp);
strcpy(temp,"\0");
/*strcpy(temp,weavestr[5]);
seats = atoi(temp);
strcpy(temp,"\0");*/
 snprintf(query,MAXLINE,"call make_reservation(%d,'%s','%s','%s','%s','%s')",customerid,weavestr[2],weavestr[3],weavestr[4],weavestr[5],weavestr[6]);
 printf("DB query made: %s\n",query);
 //pthread_mutex_lock(&mlock); //thread locked
 mysql_query(conn,query);
          printf("%llu ticket booked\n",mysql_affected_rows(conn));
          snprintf(dest,MAXLINE,"%llu ticket booked\n",mysql_affected_rows(conn));
          // pthread_mutex_unlock(&mlock); //thread unlocked
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 acknowledge;
 break; // GET_INFO ENDS
 case 3: //UPDATE_INFO
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(2,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
strcpy(temp,weavestr[1]);
customerid = atoi(temp);
strcpy(temp,"\0");
/*strcpy(temp,weavestr[5]);
seats = atoi(temp);
strcpy(temp,"\0");*/
snprintf(query,MAXLINE,"call view_reservation(%d)",customerid);

 printf("DB query made: %s\n",query);
 //pthread_mutex_lock(&mlock); //thread locked
 mysql_query(conn,query);
          res = mysql_use_result(conn);
          num_fields=mysql_num_fields(res);
          
          while ((row = mysql_fetch_row(res)) != NULL)
          {
              for(int i=0;i<num_fields;i++)
              {
                  printf("%s ", row[i] ? row[i] : "NULL");
                  sprintf(sendline,"%s ", row[i] ? row[i] : "NULL");
                  strcat(dest,sendline);
              }
              printf("\n");
              strcat(dest,"\n");
          }
          mysql_free_result(res);
           //pthread_mutex_unlock(&mlock); //thread unlocked
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 acknowledge;
 break; //UPDATE_INFO
 case 4: //REMOVE FLIGHT
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(3,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
strcpy(temp,weavestr[1]);
customerid = atoi(temp);
strcpy(temp,"\0");
strcpy(temp,weavestr[2]);
reservationid = atoi(temp);
strcpy(temp,"\0");
          snprintf(query,MAXLINE,"call cancel_reservation(%d,%d)",customerid,reservationid);

 printf("DB query made: %s\n",query);
 //pthread_mutex_lock(&mlock); //thread locked
 mysql_query(conn,query);
 printf("%llu Ticket cancelled\n",mysql_affected_rows(conn));
 snprintf(dest,MAXLINE,"%llu Ticket cancelled\n",mysql_affected_rows(conn));
  //pthread_mutex_unlock(&mlock); //thread unlocked
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 break; // REMOVE FLIGHT
  }
  }
  break;
 case 2: //AIRLINES BEGIN
 while(trx)
 {
 /*read(connfd,buffer,MAXLINE);
 strcpy(username,buffer);
 strcpy(buffer,"\0");
 acknowledge;
 read(connfd,buffer,MAXLINE);
 strcpy(password,buffer);
 strcpy(buffer,"\0");
 
 snprintf(query,MAXLINE,"SELECT loginid from ADMS_Users where UserName='%s AND Password=MD5('%s')",username,password);
    if(mysql_query(conn,query)<0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("%llu user authenticated\n",mysql_affected_rows(conn));
    if(mysql_affected_rows(conn)>0)
         write(connfd,"1",strlen("1"));
    else
        write(connfd,"0",strlen("0"));
*/read(connfd,buffer,MAXLINE);
  acknowledge;
  strcpy(container,buffer);
  option = argcomp(container);
  memset(buffer,0,MAXLINE);
  switch(option)
  {
  case 5: // ADD FLIGHT
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(6,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
strcpy(temp,weavestr[4]);
price = atoi(temp);
strcpy(temp,"\0");
strcpy(temp,weavestr[5]);
seats = atoi(temp);
strcpy(temp,"\0");
 snprintf(query,MAXLINE,"call ADMS_DB.add_flight('%s','%s','%s',%d,%d)",weavestr[1],weavestr[2],weavestr[3],price,seats);
 

 printf("DB query made: %s\n",query);
 //pthread_mutex_lock(&mlock); //thread locked
 mysql_query(conn,query);
 
 printf("%llu flight added\n",mysql_affected_rows(conn));
 snprintf(dest,MAXLINE,"%llu flight added\n",mysql_affected_rows(conn));
 // pthread_mutex_unlock(&mlock); //thread unlocked
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 acknowledge;
 break; // ADD_FLIGHT ENDS
 case 6: // GET_INFO
  pthread_mutex_lock(&mlock); //thread locked
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(4,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
 strcpy(temp,weavestr[1]);
airlineid = atoi(temp);
strcpy(temp,"\0");
 snprintf(query,MAXLINE,"CALL view_flight(%d,'%s','%s')",airlineid,weavestr[2],weavestr[3]);

 printf("DB query made: %s\n",query);
 
 mysql_query(conn,query);
          res = mysql_use_result(conn);
          num_fields=mysql_num_fields(res);
          
          while ((row = mysql_fetch_row(res)) != NULL)
          {
              for(int i=0;i<num_fields;i++)
              {
                  printf("%s ", row[i] ? row[i] : "NULL");
                  sprintf(sendline,"%s ", row[i] ? row[i] : "NULL");
                  strcat(dest,sendline);
              }
              printf("\n");
              strcat(dest,"\n");
          }
          mysql_free_result(res);
          
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 acknowledge;
 pthread_mutex_unlock(&mlock); //thread unlocked
 break; // GET_INFO ENDS
 case 7: //UPDATE_INFO
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(3,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
strcpy(temp,weavestr[1]);
flightid = atoi(temp);
strcpy(temp,"\0");
strcpy(temp,weavestr[2]);
price = atoi(temp);
strcpy(temp,"\0");
          snprintf(query,MAXLINE,"call update_flight(%d,%d)",flightid,price);

 

 printf("DB query made: %s\n",query);
 //pthread_mutex_lock(&mlock); //thread locked
 mysql_query(conn,query);
          printf("%llu flight updated\n",mysql_affected_rows(conn));
          snprintf(dest,MAXLINE,"%llu flight updated\n",mysql_affected_rows(conn));
          // pthread_mutex_unlock(&mlock); //thread unlocked
 
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 acknowledge;
 break; //UPDATE_INFO
 case 8: //REMOVE FLIGHT
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(2,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
strcpy(temp,weavestr[1]);
flightid = atoi(temp);
strcpy(temp,"\0");
snprintf(query,MAXLINE,"CALL remove_flight(%d)",flightid);
  

 printf("DB query made: %s\n",query);
 pthread_mutex_lock(&mlock); //thread locked
 mysql_query(conn,query);
 
 printf("%llu flight removed\n",mysql_affected_rows(conn));
 snprintf(dest,MAXLINE,"%llu flight removed\n",mysql_affected_rows(conn));
  pthread_mutex_unlock(&mlock); //thread unlocked
 
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 acknowledge;
 break; // REMOVE FLIGHT
  }
  }
  break;
 case 3: 
 while(trx)
 {
 /*read(connfd,buffer,MAXLINE);
 strcpy(username,buffer);
 strcpy(buffer,"\0");
 acknowledge;
 read(connfd,buffer,MAXLINE);
 strcpy(password,buffer);
 strcpy(buffer,"\0");
 
 snprintf(query,MAXLINE,"SELECT loginid from ADMS_Users where UserName='%s AND Password=MD5('%s')",username,password);
    if(mysql_query(conn,query)<0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("%llu user authenticated\n",mysql_affected_rows(conn));
    if(mysql_affected_rows(conn)>0)
         write(connfd,"1",strlen("1"));
    else
        write(connfd,"0",strlen("0"));
*/read(connfd,buffer,MAXLINE);
  acknowledge;
  strcpy(container,buffer);
  option = argcomp(container);
  memset(buffer,0,MAXLINE);
  switch(option)
  {
  case 9: // ADD_AIRLINE
  pthread_mutex_lock(&mlock); //thread locked
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(3,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */

 snprintf(query,MAXLINE,"call add_airline('%s','%s')",weavestr[1],weavestr[2]);
 

 printf("DB query made: %s\n",query);
 
 mysql_query(conn,query);
 printf("%llu airline added\n",mysql_affected_rows(conn));
 snprintf(dest,MAXLINE,"%llu airline added\n",mysql_affected_rows(conn));
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 acknowledge;
 pthread_mutex_unlock(&mlock); //thread unlocked
 break; // ADD_AIRLINE ENDS
 case 10: // VIEW_AIRLINE
  
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
 snprintf(query,MAXLINE,"call view_airlines()");
 

 printf(" DB query: %s\n",query);
 pthread_mutex_lock(&mlock); //thread locked
 mysql_query(conn,query);
 res = mysql_use_result(conn);
                    num_fields=mysql_num_fields(res);

                    while ((row = mysql_fetch_row(res)) != NULL)
                    {
                        for(int i=0;i<num_fields;i++)
                        {
                             printf("%s ", row[i] ? row[i] : "NULL");
                             sprintf(sendline,"%s ", row[i] ? row[i] : "NULL");
                             strcat(dest,sendline);
                        }
                        printf("\n");
                        strcat(dest,"\n");
                    }
                    mysql_free_result(res);
                   pthread_mutex_unlock(&mlock); //thread unlocked
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 acknowledge;
 break; // VIEW_AIRLINE ENDS
 case 11: //REMOVE_AIRLINE
  read(connfd,buffer,MAXLINE);
  snprintf(buffern,MAXLINE,buffer);
  strcpy(buffer,"\0");
  weavestr = array_unpack(3,buffern);
  /*For testing
  printf("Buffern before unpacking %s\n",buffern);
  printf("Unpacked array is as follows...\n");
  for(int i=0;i<6;i++)
  {
  printf("%s\n",weavestr[i]);
  }*/
/* SQL call for adding flight */
/*Using temp to convert string from 2D string array to integer */
 
 snprintf(query,MAXLINE,"delete from airline where AirlineName='%s' AND HeadQuarters='%s'",weavestr[1],weavestr[2]);

 printf("DB query made: %s\n",query);
 //pthread_mutex_lock(&mlock); //thread locked
 mysql_query(conn,query);
 printf("%llu airline removed\n",mysql_affected_rows(conn));
 snprintf(dest,MAXLINE,"%llu airline removed\n",mysql_affected_rows(conn));
 strcpy(message,dest);
 write(connfd,message,strlen(message));
 read(connfd,trxstr,1);
 trx = atoi(trxstr);
 acknowledge;
 break; //REMOVE_AIRLINE ENDS
  }
  }
  break; //SYSADMIN ENDS
  default: break; 
 }
 

 for(int i=0;i<9;i++)
 {
 free(weavestr[i]);
 }
free(weavestr);
free(buffern);
free(ptr);
exit(0);
}


int main(int argc, char **argv)
{struct db_intr *sqlobj = malloc(sizeof(struct db_intr));
 struct sockaddr_in sock_var;
 int listenfd=socket(AF_INET,SOCK_STREAM,0);
 int connfd;
 int i;
 pthread_t t[20];
 MYSQL *conn;
 sock_var.sin_addr.s_addr=INADDR_ANY;
 sock_var.sin_port=htons(SERV_PORT);
 sock_var.sin_family=AF_INET;

    conn = mysql_init(NULL);
sqlobj->conn = malloc(sizeof(MYSQL));
printf("Listenfd value: %d\n",listenfd);
    if( conn == NULL )
     {                                               
        printf("Failed to initate MySQL\n");
        return 1;
    }
    if( ! mysql_real_connect(conn,host,user_name,pass_word,database,0,NULL,0) )
    {
        printf( "Error connecting to database: %s\n", mysql_error(conn));
        return 1;
    } 
  sqlobj->conn = conn;
 if(bind(listenfd,(struct sockaddr*)&sock_var,sizeof(sock_var))>=0)
 {
 
  printf("Socket has been created\n");
  listen(listenfd,0); 
   while(1)        //loop infinity
  {
   for(i=0;i<20;i++)      //can support 20 clients at a time
   {
    connfd=accept(listenfd,NULL,NULL);
    printf("Connected to client %d\n",connfd);
    sqlobj->connfd = connfd;
    pthread_create(&t,NULL, centreserver,(void *)sqlobj);
   }
   }
    close(listenfd);
 }
 else{
  printf("Socket creation failed\n");
 }
 free(sqlobj->conn);
 free(sqlobj);
 return 0;
}
