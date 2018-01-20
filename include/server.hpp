#ifndef DEF_SERVER
#define DEF_SERVER

#include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>
#include "fruit.hpp"
#include "snake.hpp"
#include "netconstants.hpp"

class GameServer;

int rand_ab (int a, int b)
{
  return rand() % (b-a) + a;
}

class Client
{
friend class GameServer;
public:
  Client(sf::IpAddress address, short unsigned int port/*, unsigned int id*/);
private:
  unsigned int id;
  sf::IpAddress address;
  short unsigned int port;
  Snake snake;

};

class GameServer
{
public:
  GameServer();
  void run();

private:
  sf::UdpSocket socket;
  std::vector<Client> clients;
  std::vector<Fruit> fruits;
};



#endif
