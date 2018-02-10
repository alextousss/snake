#include "server.hpp"

using namespace sf;
using namespace std;

int rand_xyz (int a, int b)
{
  return rand() % (b-a) + a;
}

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
    fruits.push_back( Fruit( Vector2f(rand_xyz(0,100) * 10,rand_xyz(0,100) * 10) , 10 ) );
}

void GameServer::run()
{
  IpAddress sender_address;
  short unsigned int sender_port;
  Packet packet;
  while(true)
  {
    while( socket.receive( packet, sender_address, sender_port ) != sf::Socket::NotReady )
    {
			bool sender_known = false;

      for( unsigned int i = 0 ; i < clients.size() ; i++ )
      {
        if( clients[i].address == sender_address && clients[i].port == sender_port )
        {
					sender_known = true;
					int packet_type;
					if ( packet >> packet_type )
					{
						switch ( packet_type )
						{
							case SEND_INPUT:
								Uint8 asked_direction;
								if( packet >> asked_direction )
								{
									clients[i].snake.setDirection( static_cast<direction_t>(asked_direction) );
                  cout << static_cast<direction_t>(asked_direction) << endl;
								}
								break;
						}
					}
        }
      }
			if( !sender_known )
			{
				clients.push_back( Client( sender_address, sender_port, clients.size() ) );
        for ( Fruit &f : fruits ) // on lui envoie tout les fruits
        {
          Packet packet;
          packet << SEND_FRUIT << f.getPosition().x << f.getPosition().y;
          socket.send( packet, sender_address, sender_port );
        }


        Packet packet;
        packet << CONNECT << clients.back().getId();
        socket.send( packet, sender_address, sender_port );
				cout << "new client : " << sender_address << ":" << sender_port << endl;
			}
    }

		for( unsigned int i = 0 ; i < clients.size() ; i++ )
		{
      Packet packet;

			clients[i].snake.update();
			if( clients[i].snake.hasAdvanced() )
			{
				packet << SEND_SNAKE << clients[i].getId() << clients[i].snake.getState() << clients[i].snake.getSize() << static_cast<Uint8>(clients[i].snake.getLastDirection());

				for( unsigned int j = 0 ; j < SNAKE_COORDS_BY_STEP ; j++ )                     //we add in the packet the last 5 states of the snake
					packet << clients[i].snake.getCoords()[j].x << clients[i].snake.getCoords()[j].y;
        for( unsigned int j = 0 ; j < clients.size() ; j++ )        //than we broadcast the packet to all players
          socket.send( packet, clients[j].address, clients[j].port);
      }
		}

  }
}
