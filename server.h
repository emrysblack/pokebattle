//
//  server.h
//  PokeBattleProj
//
//  Created by Joshua Comish on 3/16/15.
//  Copyright (c) 2015 Joshua Comish. All rights reserved.
//
#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <netinet/in.h> 
#include <iostream>
#include "attack.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
using namespace std;

class Server 
{
    public:
    static int portNum;
    static int serverSocket;
    static int clientSocket;
    static int player1;
    static bool findClient()
    {
        portNum = 5000;
        int clilen1;
        
        char buffer[1];
        struct sockaddr_in serv_addr, p1_addr;
        struct sockaddr_in serv_addr1;
        struct hostent *server;
        
        if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
           cerr << "server: can't open stream socket";
        
        bzero((char *) &serv_addr, sizeof(serv_addr));
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portNum);

        //automatically generate a port number
        while (::bind(serverSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        {
           portNum++;
           serv_addr.sin_port = htons(portNum);
        }

        //inform the user of his/her port
        cout << endl << "PORT:" << portNum << endl << endl;
        
        //start the server, listen for clients
        listen(serverSocket, 5);
        
        string targetHost;
        cout << "Enter other player's hostname: ";
        cin >> targetHost;
        
        int targetPort;
        cout << "Enter other player's port number: ";
        cin >> targetPort;
        
        //connect to the server
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        server = gethostbyname(targetHost.c_str());
        if (server == NULL)
        {
           cerr << "ERROR: no such host.\n";
           exit(0);
        }
        
        bzero((char *) &serv_addr, sizeof(serv_addr1));
        serv_addr1.sin_family = AF_INET;
        bcopy((char *)server->h_addr,
              (char *)&serv_addr1.sin_addr.s_addr,
              server->h_length);
        serv_addr1.sin_port = htons(targetPort);
        
        if (connect(clientSocket,(struct sockaddr *) &serv_addr1,sizeof(serv_addr1)) < 0)
           cerr << "ERROR connecting!\n";
        
        cout << "listening for 1 client\n";
        player1 = accept(serverSocket, 0, 0);
        
        buffer[0] = 1;
        write(player1, buffer, 1);
        read(clientSocket, buffer, 1);
        
        return true;
    }
    
    static void sendAttack(const Attack & attack)
    {
       char buffer[6];
       // ready the buffer
       buffer[0] = attack.accRole;
       buffer[1] = attack.dRole;
       buffer[2] = attack.critRole;
       buffer[3] = attack.moveNum;
       buffer[4] = attack.pokeNum;
       buffer[5] = '\0';

       // send the data
       write(player1, buffer, 5);
    }
    
    static Attack receiveAttack()
    {
       char buffer[6];
       // receive data
       read(clientSocket, buffer, 5);
       int a = buffer[0];
       int d = buffer[1];
       int c = buffer[2];
       int m = buffer[3];
       int p = buffer[4];
       Attack attack(a, d, c, m, p);
       
       //build a move object using the raw data recieved
       return attack;
    }
};


#endif
