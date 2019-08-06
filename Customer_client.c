#include "adms.h"


int main(int argc, char** argv)
{   char kind[] = {"customer"}; char ack[3];
char buffer[MAXLINE];
    struct sockaddr_in sock_var;
 int connfd=socket(AF_INET,SOCK_STREAM,0);
 char trxstr[1],str_ser[20], arg_address[15], smallstr[50],largestr[200],dummy[10];
 char *maxstr= (char*)malloc(sizeof(char)*1500);
 
 char **weavestr = malloc(sizeof(char)*MAXLINE);
 for(int i=0;i<9;i++)
 {
 weavestr[i] = malloc(sizeof(char)*20);
 }
 
 int trx =1, login=1;
 int option,option2;
 
 sock_var.sin_addr.s_addr=INADDR_ANY;
 sock_var.sin_port=htons(SERV_PORT);
 sock_var.sin_family=AF_INET;
 printf("Connfd: %d\n",connfd);
 if(connfd<0)
 {
 perror("Connfd <0");
 exit(-1);
 }
 if(connect(connfd,(struct sockaddr*)&sock_var,sizeof(sock_var))>=0)
 {
  printf("Connected to server %d\n",connfd);
  /*sending kind of client*/
  write(connfd,kind,strlen(kind));
  read(connfd,ack,3);
  while(trx)
  {/*while(login)
  {
  printf("===================================================================\n");
  printf("Enter Username: ");
  scanf("%s",smallstr);
  write(connfd,smallstr,MAXLINE);
  strcpy(smallstr,"\0");
  read(connfd,smallstr,MAXLINE);
  strcpy(smallstr,"\0");
  printf("\nEnter Password: ");
  scanf("%s",smallstr);
  write(connfd,smallstr,MAXLINE);
  strcpy(smallstr,"\0");
  read(connfd,smallstr,MAXLINE);
  printf("After pass we recieved: %s",smallstr);
  option = atoi(smallstr);
  if(option == 1)
  { printf("\nLogin successful\n");
  login=0;
  break;}
  else
  {printf("\nInvalid Username or Password\n");
  continue;
  }
  }*/
  printf("===================================================================\n\n");
  printf("Welcome to the Customer Portal: \n\n");
    printf("===================================================================\n\n");
  printf("Avaiable commands...\n");
  printf("<inquire_reservation> to enquire about a reservation.\n");
  printf("<make_reservation> to book a flight.\n");
  printf("<view_reservation> to view a particular reservation.\n");
  printf("<cancel_reservation> to cancel a existing reservation.\n");
  printf("Enter your command here:");
  scanf("%s",weavestr[0]);
  strcpy(buffer,weavestr[0]);
  write(connfd,buffer,MAXLINE);
  memset(buffer,0,MAXLINE);
  read(connfd,ack,3);
  option2 = argcomp(weavestr[0]);
  //printf("\noption value is %d",option2);
  switch(option2){
  case 1:
          printf("\n===================================================================\n\n");
          fgets(dummy,10,stdin);
          printf("\nEnter To Location: ");
          fgets(weavestr[1],50,stdin);
          clearn(weavestr[1]);
          printf("\nEnter From Location: ");
          fgets(weavestr[2],50,stdin);
          clearn(weavestr[2]);
          //printf("\nEnter Travel Date: ");
          //fgets(weavestr[3],50,stdin);;
          //clearn(weavestr[3]);
          maxstr = array_pack(3,weavestr);
          strcpy(buffer,maxstr);
          //printf("\n packed string is %s\n",maxstr);
          write(connfd,maxstr, strlen(maxstr));
          memset(buffer,0,MAXLINE);
          read(connfd,buffer,MAXLINE);
          printf("%s",buffer);
          printf("\n===================================================================\n\n");
          printf("Press 1 to perform another operation or 0 to exit: ");
          scanf("%s",trxstr);
          trx = atoi(trxstr);
          write(connfd,trxstr,1);
          read(connfd,ack,3);
          break;
  case 2:
          printf("\n===================================================================\n\n");
          fgets(dummy,10,stdin);
          printf("Enter Customer ID: ");
          fgets(weavestr[1],50,stdin);
          clearn(weavestr[1]);
          printf("\nDate of birth: ");
          fgets(weavestr[2],50,stdin);
          clearn(weavestr[2]);
          printf("\nEnter To Location: ");
          fgets(weavestr[3],50,stdin);
          clearn(weavestr[3]);
          printf("\nEnter From Location : ");
          fgets(weavestr[4],50,stdin);
          clearn(weavestr[4]);
          printf("\nEnter Airline: ");
          fgets(weavestr[5],50,stdin);;
          clearn(weavestr[5]);
          printf("\nEnter Travel Date: ");
          fgets(weavestr[6],50,stdin);;
          clearn(weavestr[6]);
          maxstr = array_pack(7,weavestr);
          strcpy(buffer,maxstr);
          //printf("\n packed string is %s\n",maxstr);
          write(connfd,maxstr, strlen(maxstr));
          memset(buffer,0,MAXLINE);
          read(connfd,buffer,MAXLINE);
          printf("%s",buffer);
          printf("\n===================================================================\n\n");
          printf("Press 1 to perform another operation or 0 to exit: ");
          scanf("%s",trxstr);
          trx = atoi(trxstr);
          write(connfd,trxstr,1);
          read(connfd,ack,3);
          break;
  case 3:
          printf("\n===================================================================\n\n");
          fgets(dummy,10,stdin);
          /*printf("Enter Airline Name: ");
          fgets(weavestr[1],50,stdin);
          clearn(weavestr[1]);
          printf("\nEnter To Location: ");
          fgets(weavestr[2],50,stdin);
          clearn(weavestr[2]);
          printf("\nEnter From Location: ");
          fgets(weavestr[1],50,stdin);
          clearn(weavestr[1]);*/
          printf("\nEnter Customer ID: ");
          fgets(weavestr[1],50,stdin);
          clearn(weavestr[1]);
          /*
          printf("\nEnter total number of seats: ");
          fgets(weavestr[5],50,stdin);;
          clearn(weavestr[5]);*/
          maxstr = array_pack(2,weavestr);
          strcpy(buffer,maxstr);
          //printf("\n Packed string is %s\n",maxstr);
          write(connfd,maxstr, strlen(maxstr));
          memset(buffer,0,MAXLINE);
          read(connfd,buffer,MAXLINE);
          printf("%s",buffer);
          printf("\n===================================================================\n\n");
          printf("Press 1 to perform another operation or 0 to exit: ");
          scanf("%s",trxstr);
          trx = atoi(trxstr);
          write(connfd,trxstr,1);
          read(connfd,ack,3);
          break;
  case 4:
          printf("\n===================================================================\n\n");
          fgets(dummy,10,stdin);
          /*printf("Enter Airline Name: ");
          fgets(weavestr[1],50,stdin);
          clearn(weavestr[1]);
          printf("\nEnter To Location: ");
          fgets(weavestr[2],50,stdin);
          clearn(weavestr[2]);
          printf("\nEnter From Location: ");
          fgets(weavestr[1],50,stdin);
          clearn(weavestr[1]);*/
          printf("\nEnter Customer id: ");
          fgets(weavestr[1],50,stdin);
          clearn(weavestr[1]);
          printf("\nEnter Reservation id: ");
          fgets(weavestr[2],50,stdin);;
          clearn(weavestr[2]);
          maxstr = array_pack(3,weavestr);
          strcpy(buffer,maxstr);
          //printf("\n packed string is %s\n",maxstr);
          write(connfd,maxstr, strlen(maxstr));
          memset(buffer,0,MAXLINE);
          read(connfd,buffer,MAXLINE);
          printf("%s",buffer);
          printf("\n===================================================================\n\n");
          printf("Press 1 to perform another operation or 0 to exit: ");
          scanf("%s",trxstr);
          trx = atoi(trxstr);
          write(connfd,trxstr,1);
          read(connfd,ack,3);
          break;

  default:
  printf("Default");
  break;
  }  
  
  
 } close(connfd);
 
 }
 else{
  printf("\nSocket creation failed");

     
}
for(int i=0;i<9;i++)
 {
 free(weavestr[i]);
 }
free(weavestr);
free(maxstr);
  return 0;
}

