# CS 455/555: Programming Project 3 - Distributed Identity Server (Phase II)

* Andrew Haddon, Senami Hodonu
* Class: CS455  [Distributed Systems] Section #1


## Overview

The goal of this project is to improve the reliability of the identity server created in the phase I of this project. Multiple copies of the server will be run to acheive improved riabilty. Listed below are some of the specifications provided for this project:
- At any time there is only one server that all clients are using.
- The servers need to elect a leader amongst themselves. The leader serves the clients. The leader also checkpoints the state to disk and with other servers.
- If a leader goes down or becomes inaccessible, then a new election is held and another server takes over the job of the leader. There should no loss of state in this transition (within the inconsistency window that we define)
- How does a client discover a new server? You can come up with any solution. However it should be possible in your solution for the client to discover the new leader dynamically. 

## Manifest

- Client_Truststore: Store certificates from Certified Authorities (CA) that verify the certificate presented by the server in an SSL connection (Client). 
- Mysecurity.policy: Permissions
- Server.cer: Generated Certificate
- Server_Keystore: Store certificates from Certified Authorities (CA) that verify the certificate presented by the server in an SSL connection (Server).
- ClientHelp.java: Helper class for IdClient.java
- IdClient.java: The client side of the RMI application it uses command line input and reach out to the server with the input and expects results.
- IdentityServerBackend.java: File containing all the operations relevant to manipulating a mysql database containing the entries for the IDs
- IdentityServerInterface.java: The interface necessary to make RMI work, is implemented by IndenityServerBackend.
- IdServer: The landing site and RMI host the functions attached to the RMI are provide by IdentityServerBackend.
- SQLiteConn: the connection class for the mysql server
- Identity_Server_unit_Test: a sweet of unit tests to test Identity server backend
- Server2Server.java: Helper class to aid communication between servers
- Server2ServerInterface.java: The interface necessary to make RMI work, is implemented by Server2Server.
- sqlite-jdbc-3.36.0.3.jar : a support jar for SQlite
- rmi-startup - Start the RMI process and compile the program
- rmi-finish - Kill any lingering process and make clean
- run-client - run the IdClient
- run-server - run the IdServer
- printScript - Test scripp for the print option
- lookUpScript - Test scripp for the look up option
- deleteScript - Test scripp for the delete option
- createScript - Test scripp for the create option
- Dockerfile - Docker recipe to run the IdServer


## Building the project

To build this program, in the directory containing the program (p3), the make command is issued:

$ make

After a successful build, the following command is issued to change directory into the main directory with the compiled program source files:

$ cd p3/src

In the main directory, the following commands are issued to run the program:

Server side:

$ "Usage: java -classpath ".:sqlite-jdbc-3.36.0.3.jar" ids.server.IdServer [--numport <port#>] [--verbose]"

Port number range: 5156 - 5160

Client side (on a different terminal):

$ "usage: java -classpath ".:sqlite-jdbc-3.36.0.3.jar" ids.server.IdClient --server <serverhost> [--numport <port#>] <query>"

### Using the scripts on onyx
  1. Run the rmi-startup script to start the RMI
  2. In a different terminal, run the run-server script (one for each onyx node)
  3. The run-client script with appropiate arguments can be run to run the client

## Features and usage

This program is an extension or better put a replication of the Identity server form the previous project. Unlike the previous server there are multiple servers that all contain backups of all write requests done on the database replicated to all other database to ensure reduency should a server fail. The other large step made in this project is a coordinator server that acts as a central hub for requests the other severs preform elections to elect a coordinator. 

To use this program you will first need to collect a list of the IP address you inted to use for servesr as they need to be hardwired at the top of IdServer.java. Then compile all of the java files using the make file, simply use the command make in the folder that contains all of the java files. You will then need to run the server with java -classpath ".:sqlite-jdbc-3.36.0.3.jar" ids.server.IdServer  --numport<port#>  --verbose on the machines who IP address you identified. Then run the client java -classpath ".:" ids.server.IdClient -s  <server> -c <command> if you just run this you will see a list of commands and their usage.

To use the docker file you need to have the docker file and the src file from project 3 in the same directory and the dockerfile copies the src folder into the container to compile and use the server files as well as the database. Once they are collected you can create and instance by running “sudo docker build -t p3 .” .

## Testing
Testing for this iteration of Identity server bailed out on the unit tests of the last project as they put to much stress on the database. I think I found a way around that but decided to doge the issue all together. Testing was performed on both onyx and docker containers as onyx shares the same memory area making it inconducive to test SQLite database replication. Actually testing was done via running commands and examineing the database after the operation using a tool called DB browser the same tool used to create SQLite files (.db). 

## Known Bugs
Docker and SQLite have a strange interaction where writing to the database works well but reading from the database aways returns a null. 

## Reflection
As the program I work on have grown more complex I have found that I spend more time drawing and less time programing % wise when working on a project, This is the closest I have ever come to tipping the 50% mark as far more time went into designing this project then coding but based of the buggy nature of this project I maybe should of spent more time coding. 

At the start of the project it was assumed that a 2nd RMI would be required to handle replication cross the databases , at a certain point the realization dawned that the same RMI was useable to server as both the receiver for the Client connection and the replication as many of the new methods where private with only the new command to write new query’s and to reach out to secure the list of new queries sense the server was last up. This reduced the complexity greatly. 

The 2nd less great realization that delete operations are in fact write operations and need to have there own timestamp and replication. This is when I realized I could not just ask the database for all entries after a timestamp and be alright. To solve this issue each server keeps a arraylist backup containg the query and timestamp to make it easy for a sever to catch back up.

Lastly docker, setting up docker was easy thanks to homework 3 I was able to reuse most of the dockerfile for this project. The issue I had with docker as previously mentioned when it copied the .db file into the docker container it seemed to lose the ability to read form it and only be able to write to it except for creating a user. I know that the sql still worked as I tested it locally when I was have issues getting it to work on docker.

Implementing the election algorithm was very challenging. It was a understanding how to iterate through the list of processes to deduce their process identications. It took a while to come with the required steps and methods necessary to implement the bully algorithm. The election algorithm was not implemented as gracefully as we would like it. The TimerCheck tool was useful for setting up a heartbeat check between servers.


YouTube: https://youtu.be/ackUWaBKG1M

## Sources used

https://www.geeksforgeeks.org/sha-256-hash-in-java/

[Here is some help creating links](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#links)
