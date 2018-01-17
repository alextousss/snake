#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "fruit.hpp"
#include "snake.hpp"
#include "dynamicView.hpp"

using namespace sf;
using namespace std;

#define SCREEN_HEIGHT 1400
#define SCREEN_WIDTH 800

int main()
{
	RenderWindow window(sf::VideoMode(SCREEN_HEIGHT,SCREEN_WIDTH), "Snake du bg");
	window.setVerticalSyncEnabled(true);

	DynamicView view;

	Snake snake(Vector2f(500,500), 10);
	vector<Fruit> fruits;
	for(unsigned int i = 0 ; i < 100 ; i++)
		fruits.push_back( Fruit( Vector2f(i*20, i*10 ), 10.f ) );

	view.setSize( Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH) );

	while(window.isOpen())
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


		view.update( snake.getPosition() );
		window.setView( view );


		snake.update();


		window.clear(Color(0,0,0));

		for( Fruit& f : fruits )
			window.draw( f );
		window.draw(snake);

		window.display();
	}

	return 0;
}
