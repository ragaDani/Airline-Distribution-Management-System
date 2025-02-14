# Airline Distribution Management System

Airline Distribution Management System is built to interact with multiple airline and customer clients to keep the airline ecosystem alive. The ADMS is an ecosystem designed leveraging client-server model using socket programming in C. We have the following entities interacting with each other keep the ecosystem working. The system is designed to operate using both IPv4 and IPv6 protocols.

* Centralised server: A centralised server interacts with Airline and Customer clients. The main operation of centralised server is to recieve messages from clients, interface with central database and return results to the clients.

* Airline client: The airline client interacts with centralised server to manage information about airlines available for a route.

* Customer client: The customer client interacts with centralised server to manage information about customers who reserve tickets for travel on a specific airline.

* Central Database: MySQL database was used to interact with the centralised server to store all data recieved from its clients. To run the Makefile, MySQL needs to be installed in the host system.

*Please note that this not a commercial grade server-client implementation, it was developed only to learn socket programming during my network programming course at school. Please refer to this repository only for learning purposes.*


