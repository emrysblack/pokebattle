//
//  server.h
//  PokeBattleProj
//
//  Created by Joshua Comish on 3/16/15.
//  Copyright (c) 2015 Joshua Comish. All rights reserved.
//

#include "iostream"
using namespace std;

static class server
{
    int portNum;
    int serverSocket;
    int clientSocket;
    
    void setPortNum(int port) {portNum = port;}
    bool findClient()
    {
        cout << "Enter other player's port number: ";
        return true;
    }
    
};

