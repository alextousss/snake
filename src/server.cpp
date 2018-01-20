#include "server.hpp"

using namespace sf;
using namespace std;

Client::Client(sf::IpAddress address, short unsigned int port/*unsigned int id*/) : snake(Vector2f(10,10) ,10.0f)
{
 // this->id = id;
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
			bool sender_known = false;

      for( unsigned int i = 0 ; i < clients.size() ; i++ )
      {
        if( clients[i].address == sender_address && clients[i].port == sender_port )
        {
					sender_known = true;
					Uint8 packet_type;
					if ( packet >> packet_type )
					{
						switch ( packet_type )
						{
							case SEND_INPUT:
								Uint8 asked_direction;
								if( packet >> asked_direction )
								{
									clients[i].snake.setDirection( static_cast<direction_t>(asked_direction) );
								}
								cout << "input : " << asked_direction << endl;
								break;
						}
					}
        }
      }
			if( !sender_known )
			{
				clients.push_back( Client( sender_address, sender_port ) );
				cout << "new client : " << sender_address << ":" << sender_port << endl;
			}
    }

		for( unsigned int i = 0 ; i < clients.size() ; i++ )
		{
			clients[i].snake.update();
			if( clients[i].snake.hasAdvanced() )
			{
				Packet packet;
				packet << SEND_SNAKE << clients[i].snake.getState();
				for( unsigned int j = 0 ; j < 5 ; j++ )
				{
					packet << clients[i].snake.getCoords()[j].x << clients[i].snake.getCoords()[j].y;
				}
				socket.send( packet, clients[i].address, clients[i].port);
			}
		}
		
		
  }
}
