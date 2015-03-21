// driver program for poke
#include <iostream>
#include <string>
#include <cstdlib> // for random numbers
#include "trainer.h"
#include "pokemon.h"
#include "move.h"
#include "server.h"
#include "game.h"
using namespace std;

int Server::portNum;
int Server::serverSocket;
int Server::clientSocket;
int Server::player1;
void mSetUp()
{
   Server::findClient();
}

void interact()
{
   cout << "                                  Welcome to Pokemon!\n";
    
    cout << "                                          .::.                            \n"
    << "                                        .;:**'                            \n"
    << "                                        '                                 \n"
    << "             .:XHHHHk.              db.   .;;.     dH  MX                 \n"
    << "           oMMMMMMMMMMM       ~MM  dMMP :MMMMMR   MMM  MR      ~MRMN      \n"
    << "           QMMMMMb  \"MMX       MMMMMMP !MX' :M~   MMM MMM  .oo. XMMM 'MMM \n"
    << "             `MMMM.  )M> :X!Hk. MMMM   XMM.o\"  .  MMMMMMM X?XMMM MMM>!MMP \n"
    << "              'MMMb.dM! XM M'?M MMMMMX.`MMMMMMMM~ MM MMM XM `\" MX MMXXMM  \n"
    << "               ~MMMMM~ XMM. .XM XM`\"MMMb.~*?**~ .MMX M t MMbooMM XMMMMMP  \n"
    << "                ?MMM>  YMMMMMM! MM   `?MMRb.    `\"\"\"   !L\"MMMMM XM IMMM   \n"
    << "                 MMMX   \"MMMM\"  MM       ~%:           !Mh.\"\"\" dMI IMMP   \n"
    << "                 'MMM.                                             IMX    \n"
    << "                  ~M!M                                             IMP    \n";
    cout << "                                                                  \n"
    << "                           .\"-,.__                                               \n"
    << "                           `.     `.  ,                                          \n"
    << "                        .--'  .._,'\"-' `.                                        \n"
    << "                       .    .'         `'                                        \n"
    << "                       `.   /          ,'                                        \n"
    << "                         `  '--.   ,-\"'                                          \n"
    << "                          `\"`   |  \\                                             \n"
    << "                             -. \\, |                                             \n"
    << "                              `--Y.'      ___.                                   \n"
    << "                                   \\     L._, \\                                  \n"
    << "                         _.,        `.   <  <\\                                   \n"
    << "                       ,' '           `, `.   | \\            ( `                 \n"
    << "                    ../, `.            `  |    .\\`.           \\ \\                \n"
    << "                   ,' ,..  .           _.,'    ||\\l            )  '\".            \n"
    << "                  , ,'   \\           ,'.-.`-._,'  |           .  _._`.           \n"
    << "                ,' /      \\ \\        `' ' `--/   | \\          / /   ..\\          \n"
    << "              .'  /        \\ .         |\\__ - _ ,'` `        / /     `.`.        \n"
    << "              |  '          ..         `-...-\"  |  `-'      / /        . `.      \n"
    << "              | /           |L__           |    |          / /          `. `.    \n"
    << "             , /            .   .          |    |         / /             ` `    \n"
    << "            / /          ,. ,`._ `-_       |    |  _   ,-' /               ` \\   \n"
    << "           / .           \"`_/. `-_ \\_,.  ,'    +-' `-'  _,        ..,-.    \\`.  \n"
    << "            '         .-f    ,'   `    '.       \\__.---'     _   .'   '     \\ \\  \n"
    << "          ' /          `.'    l     .' /          \\..      ,_|/   `.  ,'`     L` \n"
    << "          |'      _.-""` `.    \\ _,'  `            \\ `.___`.'\"`-.  , |   |    | \\\n"
    << "          ||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .|\n"
    << "          ||  ,'          `. ;.,.---' ,'       `.   `.. `-'  .-' /_ .'    ;_   ||\n"
    << "          || '              V      / /           `   | `   ,'   ,' '.    !  `. ||\n"
    << "          ||/            _,-------7 '              . |  `-'    l         /    `||\n"
    << "           |          ,' .-   ,' ||               | .-.        `.      .'     || \n"
    << "           `'        ,'    `\".'    |               |    `.        '. -.'       `'\n"
    << "                    /      ,'      |               |,'    \\-.._,.'/'             \n"
    << "                    .     /        .               .       \\    .''              \n"
    << "                  .`.    |         `.             /         :_,'.'               \n"
    << "                    \\ `...\\   _     ,'-.        .'         /_.-'                 \n"
    << "                     `-.__ `,  `'   .  _.>----''.  _  __  /                      \n"
    << "                          .'        /\"'          |  \"'   '_                    \n"
    << "                         /_|.-'\\ ,\".             '.'`__'-( \\                    \n"
    << "                           / ,\"'\"\\,'               `/  `-.|\\                   \n\n\n\n";

    
   Game game;
   Trainer p;
   Trainer c;
   char option = 'z';
   do
   { 
      cout << "\nWhat would you like to do? \n";
      cout << "b: battle\n";
      cout << "m: multiplayer\n";
      cout << "q: quit\n > ";
      cin >> option;
      option = tolower(option); // convert to lower case
      switch (option)
      {
         case 'b':
            game.battle(p, c);
            break;
         case 'm':
              mSetUp();
              game.netBattle(p, c);
            break;
         case 'q':
            cout << "Thanks for playing\n";
            break;
         default:
            cout << "unknown option\n";
            break;
      }
   } while (option != 'q');
}


int main(int argc, char ** argv)
{
   // prepare random 
   srand(time(NULL));
   interact();  
   return 0;
}
