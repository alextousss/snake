#include "snake.hpp"

using namespace sf;

Snake::Snake()
{
	moveByDirection = { Vector2f(-1, 0),
										  Vector2f( 0,-1),
										  Vector2f( 1, 0),
										  Vector2f( 0, 1) };

	coord.push_front( Vector2f(100.f,100.f) );
	quantum = Vector2f(10.f,10.f);
	color = Color(255,70,60);
	size = 25;

	last_update_timer.restart();
	update_period = 20;
}

Snake::Snake(Vector2f coord, float q)
{
	moveByDirection = { Vector2f( 0,-1),
											Vector2f(-1, 0),
										  Vector2f( 0, 1),
										  Vector2f( 1, 0) };
	this->coord.push_front( coord );
	quantum = Vector2f(q,q);
	color = Color(70,200,60);
	size = 25;
	update_period = 20;
}

void Snake::update( direction_t direction )
{
	choose_direction.push_back( direction );
		
	if ( last_update_timer.getElapsedTime().asMilliseconds() > update_period )
	{
		actual_direction = direction;
		coord.push_front( Vector2f(coord[0].x + quantum.x * moveByDirection[ actual_direction ].x, coord[0].y + quantum.y * moveByDirection [ actual_direction ].y) );
		
		while(coord.size() > size)
			coord.pop_back();


		vertices.setPrimitiveType(sf::Quads);
		vertices.resize( coord.size() * 4 );	
  	for( unsigned int i = 0; i < coord.size() ; i++ )
		{
			vertices[i * 4 + 0].color = color;
			vertices[i * 4 + 1].color = color;
			vertices[i * 4 + 2].color = color;
			vertices[i * 4 + 3].color = color;

			vertices[i * 4 + 0].position = sf::Vector2f( coord[i].x, coord[i].y + quantum.y); 
			vertices[i * 4 + 1].position = sf::Vector2f( coord[i].x, coord[i].y);
			vertices[i * 4 + 2].position = sf::Vector2f( coord[i].x + quantum.x, coord[i].y); 
			vertices[i * 4 + 3].position = sf::Vector2f( coord[i].x + quantum.x, coord[i].y + quantum.y); 
		}
	last_update_timer.restart();
	}
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(vertices);
}
