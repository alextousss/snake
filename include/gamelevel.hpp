#ifndef DEF_GAMELEVEL
#define DEG_GAMELEVEL
#include <SFML/Graphics.hpp>
#include <cmath>
#include <deque>
#include <iostream>
#include "fruit.hpp"
#include "snake.hpp"
#include "dynamicView.hpp"

class Gamelevel
{
private:
  std::vector<Fruit> fruits;
  Snake snake;
  DynamicView view;
  sf::RenderWindow window;
public:
  Gamelevel();
  void run();

};

#endif
