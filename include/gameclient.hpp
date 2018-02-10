#ifndef DEF_CLIENT
#define DEF_CLIENT

#include <SFML/Network.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include "dynamicView.hpp"
#include "fruit.hpp"
#include "snake.hpp"
#include "netconstants.hpp"

class GameClient;


struct Server
{
  sf::IpAddress address;
  unsigned short port;
};

class GameClient
{
public:
  GameClient(sf::IpAddress address, unsigned short port);
  void run();

private:
  unsigned int client_snake_id;
  Server server;
  sf::UdpSocket socket;
  std::map<unsigned int, Snake> snakes;
  std::vector<Fruit> fruits;
  DynamicView view;
  sf::RenderWindow window;

};



#endif
