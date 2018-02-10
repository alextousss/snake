#ifndef DEF_SNAKE
#define DEF_SNAKE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <queue>

#define UPDATE_PERIOD 110

enum direction_t { NORTH, WEST, SOUTH, EAST };


class Snake : public sf::Drawable
{
public:
	Snake();
	Snake(sf::Vector2f coord, float q);

	void addCoords(std::vector<sf::Vector2f>& coords, unsigned int coords_state);
	void update();
	void setDirection( direction_t direction);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool hasAdvanced();
	direction_t getLastDirection() 							{ return next_direction ; }
	unsigned int getState()											{ return state ; }
	void setSize( unsigned int new_size ) 			{ size = new_size ; }
	unsigned int getSize() 															{ return size ;}
	sf::Vector2f getHeadPosition() 							{ return coord[0] ; }
	std::deque<sf::Vector2f>& getCoords() 			{ return coord ; }
private:
	bool has_advanced;
	std::deque<sf::Vector2f> coord;
	sf::Vector2f quantum;
	unsigned int size;

	sf::Color color;
	sf::VertexArray vertices;

	std::queue<direction_t> choose_direction;
	direction_t actual_direction;
	direction_t next_direction;
	std::array<sf::Vector2f, 4> moveByDirection;
	sf::Clock last_update_timer;
	unsigned int state;
	int update_period;
};



#endif
