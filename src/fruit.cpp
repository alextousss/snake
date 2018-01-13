#include "fruit.hpp"

using namespace sf;

Fruit::Fruit()
{
	coord = Vector2f(100.f,100.f);
	taille = Vector2f(10.f,10.f);
	color = Color(255,0,0);
	type = NOURRITURE;

	rectangle.setFillColor(color);
	rectangle.setPosition(coord);
	rectangle.setSize(taille);
}

Fruit::Fruit(Vector2f coord, float q)
{
	this->coord = coord;
	taille = Vector2f(q,q);
	color = Color(255,0,0);
	type = NOURRITURE;

	rectangle.setFillColor(color);
	rectangle.setPosition(coord);
	rectangle.setSize(taille);
}

void Fruit::update()
{
	rectangle.setFillColor(color);
	rectangle.setPosition(coord);
	rectangle.setSize(taille);
}

void Fruit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rectangle);
}
