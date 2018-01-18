#ifndef DEF_FRUIT
#define DEF_FRUIT

#include <SFML/Graphics.hpp>

class Fruit : public sf::Drawable
{
public:
	Fruit();
	Fruit(sf::Vector2f coord, float q);
	void update();
	sf::Vector2f getPosition() { return coord ; }
	void eat() { ; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Vector2f coord;
	sf::Vector2f taille;
	sf::Color color;
	sf::RectangleShape rectangle;
	enum type_e {VITESSE, NOURRITURE};
	type_e type;

};


#endif
