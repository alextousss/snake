#include "server.hpp"

using namespace sf;

Client::Client(sf::IpAddress address, short unsigned int port, unsigned int id) : snake(Vector2f(10,10) ,10.0f)
{
  this->id = id;
  this->address = address;
  this->port = port;
}

GameServer::GameServer()
{
  socket.bind(27563);
  socket.setBlocking(false);
  for( unsigned int i = 0 ; i < 250 ; i++ )
    fruits.push_back( Fruit( Vector2f(rand_ab(0,500),rand_ab(0,500)) , 10 ) );
}

void GameServer::run()
{
  IpAddress sender_address;
  short unsigned int sender_port;
  Packet packet;
  while(true)
  {
    while( socket.receive( packet, sender_address, sender_port ) )
    {
      for( unsigned int i = 0 ; i < clients.size() ; i++ )
      {
        if( clients[i].address == sender_address && clients[i].port == sender_port )
        {

        }
      }
    }
  }
}
