#include "gameclient.hpp"

#define SCREEN_HEIGHT 1400
#define SCREEN_WIDTH 800
using namespace sf;
using namespace std;

GameClient::GameClient(sf::IpAddress address, unsigned short port) : window(sf::VideoMode(SCREEN_HEIGHT,SCREEN_WIDTH), "Snake du bg")
{
  window.setVerticalSyncEnabled(true);
  server = { address, port };
  view.setSize( Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH) );

  socket.setBlocking(false);
}

void GameClient::run()
{
  Packet packet;
  packet << CONNECT;
  socket.send( packet, server.address, server.port );

  Packet incoming_packet;
  IpAddress server_address;
  unsigned short port;
  bool init_finished = false;
  while( !init_finished )
  {
    if( socket.receive( incoming_packet, server_address, port ) != Socket::NotReady )
    {
      int packet_type;
      incoming_packet >> packet_type;

      switch ( packet_type )
      {
        case CONNECT:
          incoming_packet >> client_snake_id;
          cout << "init finished" << endl;
          init_finished = true;
          break;
        case SEND_FRUIT:
          Vector2f coords;
          incoming_packet >> coords.x >> coords.y;
          cout << coords.x << " " << coords.y << endl;
          fruits.push_back( Fruit( coords , 10.0f) );
          break;
      }
    }
  }
  while( window.isOpen() )
  {
    vector<direction_t> direction_stack;
    Event event;
    while(window.pollEvent(event))
    {
      if(event.type == Event::KeyPressed)
      {
        if(event.key.code == Keyboard::Escape)
          window.close();
        if(event.key.code == Keyboard::Z)
          direction_stack.push_back( NORTH );
        if(event.key.code == Keyboard::Q)
          direction_stack.push_back( WEST );
        if(event.key.code == Keyboard::S)
          direction_stack.push_back( SOUTH );
        if(event.key.code == Keyboard::D)
          direction_stack.push_back( EAST );
      }
      if(event.type == Event::Closed)
        window.close();
    }
    if(direction_stack.size() > 0)
    {
      snakes[client_snake_id].setDirection( direction_stack.back() );
      Packet packet;
      Uint8 direction = static_cast<Uint8>(direction_stack.back() );
      packet << SEND_INPUT << direction;

      socket.send( packet, server.address, server.port );
    }

    Packet incoming_packet;
    IpAddress sender_address;
    unsigned short sender_port;

    if( socket.receive( incoming_packet, server_address, sender_port ) != Socket::NotReady )
    {
      int packet_type;
      incoming_packet >> packet_type;
      switch ( packet_type )
      {
        case SEND_SNAKE:
          vector<Vector2f> coords;
          unsigned int id;
          unsigned int remote_state;
          unsigned int size;
          Uint8 direction_int;
          direction_t direction;
          incoming_packet >> id >> remote_state >> size >> direction_int;
          direction = static_cast<direction_t>(direction_int);
/*            cout << "id : " << id << endl;
          cout << "remote state : " << remote_state << endl;
          cout << "size : " << size << endl;*/
        //  cout << direction << endl;
          for(unsigned int i = 0 ; i < SNAKE_COORDS_BY_STEP ; i++)
          {
            Vector2f coord;
            incoming_packet >> coord.x >> coord.y;
            coords.push_back(coord);
          }
          snakes[id].setDirection(direction);
          snakes[id].setSize(size);
          snakes[id].addCoords(coords, remote_state);
          snakes[id].update();

          break;
      }
    }


    window.clear();
    for ( map<unsigned int, Snake>::iterator it = snakes.begin(); it != snakes.end(); ++it)
    {
      it->second.update();
      window.draw( it->second );
    }
    for( Fruit& f : fruits )
    {
      f.update();
      window.draw( f );
    }
    view.update( snakes[client_snake_id].getHeadPosition() );
    window.setView(view);
    window.display();


  }

}
