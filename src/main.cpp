#include <SFML/Graphics.hpp>
#include "fruit.hpp"
#include "snake.hpp"

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(sf::VideoMode(1200,800), "Snake du bg");
	window.setVerticalSyncEnabled(true);
	
	View view;	

	Snake snake(Vector2f(500,500), 10);	
	vector<Fruit> fruits;
	for(unsigned int i = 0 ; i < 100 ; i++)
		fruits.push_back( Fruit( Vector2f(i*20, i*10 ), 10.f ) );

	while(window.isOpen())
	{
		if(sf::Keyboard::isKeyPressed( sf::Keyboard::Z ))
			snake.update( NORTH );
		if(sf::Keyboard::isKeyPressed( sf::Keyboard::Q ))
			snake.update( WEST );
		if(sf::Keyboard::isKeyPressed( sf::Keyboard::S ))
			snake.update( SOUTH );
		if(sf::Keyboard::isKeyPressed( sf::Keyboard::D ))
			snake.update( EAST );
	
		if(sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ))
			window.close();
		
		view.setSize( Vector2f(1200,800) );
		view.setCenter( snake.getPosition() );
		window.setView( view );

		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
		}
		

		window.clear();
		for( Fruit& f : fruits )
			window.draw( f );
		window.draw(snake);
		window.display();
	}

	return 0;
}
