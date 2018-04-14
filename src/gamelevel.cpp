#include <gamelevel.hpp>

#define SCREEN_HEIGHT 1400
#define SCREEN_WIDTH 800

using namespace sf;
using namespace std;

Gamelevel::Gamelevel() : snake(Vector2f(500,500), 10), window(sf::VideoMode(SCREEN_HEIGHT,SCREEN_WIDTH), "Snake du bg")
{
//  RenderWindow window(sf::VideoMode(SCREEN_HEIGHT,SCREEN_WIDTH), "Snake du bg");
	window.setVerticalSyncEnabled(true);

  for(unsigned int i = 0 ; i < 100 ; i++)
    fruits.push_back( Fruit( Vector2f(i*20, i*10), 10.f ) );

  view.setSize( Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH) );
}

void Gamelevel::run()
{
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
    if( direction_stack.size() > 0 )
      snake.setDirection( direction_stack.back()  );

    view.update( snake.getHeadPosition() );
    window.setView( view );

    snake.update();
    Vector2f snake_head_pos = snake.getHeadPosition();
    for( unsigned int i = 0 ; i < fruits.size() ; i++ )
    {
      fruits[i].update();
      if( snake_head_pos == fruits[i].getPosition() )
      {
        fruits[i].eat();
        fruits.erase( fruits.begin() + i);
        snake.setSize( snake.getSize() + 1 );
      }
    }

    deque<Vector2f> snake_coords = snake.getCoords();
    for( unsigned int i = 1 ; i < snake_coords.size() ; i++ )
    {
      if( snake_coords[i] == snake.getHeadPosition() )
      {
        snake.setSize(1);
      }
    }



    window.clear(Color(0,0,0));

    for( Fruit& f : fruits )
      window.draw( f );
    window.draw(snake);

    window.display();
  }
}
