#ifndef DEF_SNAKE
#define DEF_SNAKE

#include <SFML/Graphics.hpp>
#include <deque>
#include <queue>

enum direction_t { NORTH, WEST, SOUTH, EAST };


class Snake : public sf::Drawable
{
public:
	Snake();
	Snake(sf::Vector2f coord, float q);
	void update();
	void setDirection( direction_t direction) { this->actual_direction = direction ; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getPosition() { return coord[0] ; }
private:
	std::deque<sf::Vector2f> coord;
	sf::Vector2f quantum;
	unsigned int size;

	sf::Color color;
	sf::VertexArray vertices;
		
	std::queue<direction_t> choose_direction
	direction_t actual_direction;
	std::array<sf::Vector2f, 4> moveByDirection;
	sf::Clock last_update_timer;
	int update_period;
};



#endif
