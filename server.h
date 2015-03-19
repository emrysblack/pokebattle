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
#include "move.h"
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
    
    static void server()
    {
        portNum = 5000;

        int player1, clilen1;
        char buffer[1];
        struct sockaddr_in serv_addr, p1_addr;
        int n1, n2;
        
        if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
           cerr << "server: can't open stream socket";
        
        bzero((char *) &serv_addr, sizeof(serv_addr));
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portNum);
        
        //bind the socket
        while (::bind(serverSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        {
           portNum++;
           serv_addr.sin_port = htons(portNum);
        }
        cout << endl << "HOST:" << portNum << endl << endl;
        bzero(buffer,1);
        
        //start the server, listen for clients
        listen(serverSocket, 5);
        
        
        
        string hostName;
        cout << "Enter other player's hostname: ";
        cin >> hostName;
        
        int targetPort;
        cout << "Enter other player's port number: ";
        cin >> targetPort;


        
        int n;
        struct sockaddr_in serv_addr1;
        struct hostent *server;
        
        //connect to the server
        targetPort = targetPort;
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        
        server = gethostbyname(hostName.c_str());
        
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
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
        clilen1 = sizeof(p1_addr);
        cerr << buffer[0] << endl;

        player1 = accept(serverSocket, 0, 0);
 
        
        buffer[0] = 1;
        n1 = (int)write(player1, buffer, 1);

        
        read(clientSocket, buffer, 1);

        return;
    }

    
    static bool findClient()
    {
        server();
        
        return true;
    }
    
    static void sendMove(Move move)
    {
        //send raw data of move
    }
    
    static Move recieveMove()
    {
        Move move;
        //build a move object using the raw data recieved
        return move;
    }
};


#endif
