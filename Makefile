Cflag = -I/usr/include/mysql -fabi-version=2 -fno-omit-frame-pointer
Libs = -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lm -lrt -ldl headers/dependencies.c
all:
	gcc -Wall -O server/Centralised_server.c $(Cflag) $(Libs) -pthread -o /bin/adms_server -w
	gcc -Wall -O clients/Airline_client.c $(Cflag) $(Libs) -o /bin/airline -w 
	gcc -Wall -O clients/Sysadmin_client.c $(Cflag) $(Libs) -o /bin/sysadmin -w
	gcc -Wall -O clients/Customer_client.c $(Cflag) $(Libs) -o /bin/customer -w
	gcc -Wall -O clients/Customer_client_ipv6.c $(Cflag) $(Libs) -o /bin/ipv6_customer -w
	gcc -Wall -O server/Centralised_server_ipv6.c $(Cflag) $(Libs) -o /bin/ipv6_adrms_server -w -pthread
