#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "gameclient.hpp"
#include "server.hpp"

using namespace sf;
using namespace std;

#define SCREEN_HEIGHT 1400
#define SCREEN_WIDTH 800

int main (int argc, char *argv[])
{
  if(argc == 1)
  {
    GameServer server;
    server.run();
  }
  else if(argc == 2)
  {
    GameClient client(argv[1], 27563);
    client.run();
  }
  else if(argc == 3)
  {
    GameClient client(argv[1], atoi(argv[2]));
    client.run();
  }
  return 0;
}
