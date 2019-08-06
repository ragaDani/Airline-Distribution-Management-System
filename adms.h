#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <mysql.h>
#include <pthread.h>

#define acknowledge write(connfd,ack,3)
#define MAXLINE 1500
#define SERV_PORT 3096
#define host "localhost"
#define user_name "root"
#define pass_word "cmpe207"
#define database "ADMS_DB"

void clearn(char*);
int argcomp(char *);
int connection_kind(char *);
char ** array_unpack(int, char*);
char * array_pack(int , char **);
struct db_intr {
/* While using the argv values convert them to relevant data type if needed 
to interact with the database */
MYSQL *conn;
int connfd;
};


