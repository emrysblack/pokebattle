//
//  server.h
//  PokeBattleProj
//
//  Created by Joshua Comish on 3/16/15.
//  Copyright (c) 2015 Joshua Comish. All rights reserved.
//
#ifndef SERVER_H
#define SERVER_H
#include "iostream"
#include "move.h"
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
    
    static bool findClient()
    {
        cout << "What port number will you use? (must be greater than 1000) : ";
        cin >> portNum;
        
        cout << "Enter other player's port number: ";
        
        
        
        
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

//int Server::portNum = 5000;
//int Server::serverSocket;
//int Server::clientSocket;

//SERVER
/***********************************************************************
 * This finction will write the response to the appropriate
 * player's socket.
 * int player - The socket to be written
 * char *value - the value to be written
 **********************************************************************/
//void wr(int player, char value)
//{
//    char buffer[1];
//    buffer[0] = value;
//    if(write(player, buffer, 1) < 0)
//    {
//        cerr << "failed to write to a player\n";
//    }
//}

/***********************************************************************
 * This will be called if there is a tie.  It will call the wr
 * and send a tie signal to both players.
 **********************************************************************/
//void tie(int p1, int p2)
//{
//    wr(p1, 8);
//    wr(p2, 8);
//}

/***********************************************************************
 * This will be called if there is a winner.  It will call the wr
 * for the appropriate values.
 * int p1 - The Winner.
 * int p2 - THe Loser.
 **********************************************************************/
//void eval(int p1, int p2)
//{
//    wr(p1, 6);
//    wr(p2, 7);
//    cerr << "sent win to player\n";
//}

/***********************************************************************
 * This function will run the server by listening for clients and
 * doing the input/output for them.
 **********************************************************************/
/*void run(int portNum)
 {
 int socketServer, player1, player2, clilen1, clilen2;
 char buffer[1];
 struct sockaddr_in serv_addr, p1_addr, p2_addr;
 int n1, n2;
 if ((socketServer = socket(AF_INET, SOCK_STREAM, 0)) < 0)
 {
 cerr <<"server: can't open stream socket";
 return;
 }
 
 bzero((char *) &serv_addr, sizeof(serv_addr));
 
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port = htons(portNum);
 
 //bind the socket
 if (bind(socketServer, (struct sockaddr *) &serv_addr,
 sizeof(serv_addr)) < 0)
 {
 cerr << "ERROR on BINDING\n";
 return;
 }
 
 bzero(buffer, 1);
 
 //start the server, listen for clients
 listen(socketServer, 5);
 cout << "listening for 1 client\n";
 clilen1 = sizeof(p1_addr);
 
 //accept the clients
 player1 = accept(socketServer, 0, 0);
 buffer[0] = 1;
 n1 = write(player1, buffer, 1);
 if (player1 < 0)
 {
 cerr << "player1 failed to accept";
 return;
 }
 cout << "looking for 2nd client\n";
 clilen2 = sizeof(p2_addr);
 
 player2 = accept(socketServer, 0, 0);
 buffer[0] = 1;
 n2 = write(player2, buffer, 1);
 if (player2 < 0)
 {
 cerr << "player2 failed to accept";
 return;
 }
 
 //input/output for the sockets
 while(true)
 {
 if(read(player1, buffer, 1) < 0)
 cerr << "read1 failed";
 n1 = buffer[0];
 
 if(read(player2, buffer, 1) < 0)
 cerr << "read2 failed";
 n2 = buffer[0];
 
 //check if the input is valid for p1 and p2
 if (n1 < 2 || n1 > 5)
 {
 buffer[0] = 9;
 n1 = write(player1, buffer, 1);
 buffer[0] = 5;
 n2 = write(player2, buffer, 1);
 }
 
 if (n2 < 2 || n2 >5)
 {
 buffer[0] = 9;
 n2 = write(player2, buffer, 1);
 buffer[0] = 5;
 n1 = write(player1, buffer, 1);
 }
 //a player quit
 if (n1 == 5 || n2 == 5)
 {
 buffer[0] = 5;
 n1 = write(player1, buffer, 1);
 n2 = write(player2, buffer, 1);
 break;
 }
 
 //a tie
 if (n1 == n2)
 {
 tie(player1, player2);
 }
 
 //player1 wins
 else if ((n1 == 2 && n2 == 4)||
 (n1 == 3 && n2 == 2)||
 (n1 == 4 && n2 == 3))
 {
 eval(player1, player2);
 }
 //player2 wins
 else
 {
 eval(player2, player1);
 }
 }
 
 //close the server, disconnect sockets
 cerr << "closing server\n";
 
 //disconnect the players
 buffer[0] = 5;
 n1 = write(player1, buffer, 1);
 n2 = write(player2, buffer, 1);
 close(socketServer);
 return;
 }
 
 
 int main(int argc, char *argv[])
 {
 if (argc < 2)
 {
 cerr << "Error: no port number supplied.\n";
 cerr << "Usage: <a.out> <socket Number>\n";
 return 0;
 }
 
 if (atoi(argv[1]) < 1000)
 {
 cerr << "Invalid port number.  Please use a port"
 << "number greater than 1000.\n";
 return 0;
 }
 
 run(atoi(argv[1]));
 return 0;
 }
 */





//CLIENT
/*int sockfd, portno, n;
 struct sockaddr_in serv_addr;
 struct hostent *server;
 
 char buffer[1];
 if (argc < 3) {
 fprintf(stderr,"Usage: %s (hostname) (port) e.g.: client aus213l19 5000\n", argv[0]);
 exit(0);
 }
 
 //connect to the server
 portno = atoi(argv[2]);
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0)
 error("ERROR opening socket");
 
 server = gethostbyname(argv[1]);
 
 if (server == NULL) {
 fprintf(stderr,"ERROR, no such host\n");
 exit(0);
 }
 
 bzero((char *) &serv_addr, sizeof(serv_addr));
 serv_addr.sin_family = AF_INET;
 bcopy((char *)server->h_addr,
 (char *)&serv_addr.sin_addr.s_addr,
 server->h_length);
 serv_addr.sin_port = htons(portno);
 
 if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
 error("ERROR connecting");
 
 if (read(sockfd, buffer, 1))
 //listen for input from the server
 while(buffer[0] != 'q')
 {
 printf("Please enter your choice (r,p,s,q): ");
 bzero(buffer,1);
 cin >> buffer;
 
 translateSend(buffer, sockfd);
 
 bzero(buffer,1);
 translateRead(buffer, sockfd);
 
 }
 close(sockfd);
 
 return 0;*/

#endif