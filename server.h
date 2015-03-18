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
    
    
    /* const int OP_MOVE1 = 1; */
    /* const int OP_MOVE2 = 2; */
    /* const int OP_MOVE3 = 3; */
    /* const int OP_MOVE4 = 4; */
    
    static void server()
    {
        cout << "What port number will you use? (must be greater than 1000) : ";
        cin >> portNum;
        
        int socketServer, player1, player2, clilen1, clilen2;
        char buffer[1];
        struct sockaddr_in serv_addr, p1_addr, p2_addr;
        int n1, n2;
        
        if ((socketServer = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            cerr << "server: can't open stream socket";
        }
        
        bzero((char *) &serv_addr, sizeof(serv_addr));
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port =htons(portNum);
        
        //bind the socket
        if (::bind(socketServer, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        {
            cerr << "ERROR on BINDING\n";
            return;
        }
        
        bzero(buffer,1);
        
        //start the server, listen for clients
        listen(socketServer, 5);
        
        
        char connected;
        cout << "Are you a host or client? (h/c)\n";
        cin >> connected;
        
        
        
        string hostName;
        cout << "Enter other player's hostname: ";
        cin >> hostName;
        
        int targetPort;
        cout << "Enter other player's port number: ";
        cin >> targetPort;
        
        if (connected == 'c')
        {
            char ready[1];
            cout << "Press enter when ready. ";
            cin.ignore();
            cin.getline(ready, 1);//cin >> ready;
        }
        
        int sockfd, portno, n;
        struct sockaddr_in serv_addr1;
        struct hostent *server;
        
        
        //if (argc < 3) {
        //    fprintf(stderr,"Usage: %s (hostname) (port) e.g.: client aus213l19 5000\n", argv[0]);
        //    exit(0);
        //}
        
        //connect to the server
        portno = targetPort;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        
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
        serv_addr1.sin_port = htons(portno);
        
        
        listen(socketServer, 5);
        
        if (connect(sockfd,(struct sockaddr *) &serv_addr1,sizeof(serv_addr1)) < 0)
            //error("ERROR connecting");
            
            read(sockfd, buffer, 1);
        
        
        
        
        
        
        
        
        cout << "listening for 1 client\n";
        clilen1 = sizeof(p1_addr);
        cerr << buffer[0] << endl;
        //accept the clients
        //if (buffer[0] != 1)
        //{
        player1 = accept(socketServer, 0, 0);
            //connected = true;
        //}
        
        buffer[0] = 1;
        n1 = (int)write(player1, buffer, 1);
        if (player1 < 0)
        {
            cerr << "player1 failed to accept";
            return;
        }
        
        cout << "SUCCESS!!\n";
        buffer[0] = 1;
        write(player1, buffer, 1);
        read(sockfd, buffer, 1);
        cerr << "BUFFER: " << buffer << endl;

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