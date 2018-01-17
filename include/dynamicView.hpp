#ifndef DEF_DYNAMICVIEW
#define DEF_DYNAMICVIEW

#include <SFML/Graphics.hpp>
#include <cmath>

class DynamicView : public sf::View
{
public:
  DynamicView() : sf::View() { is_in_transition = false ; }
  void update( sf::Vector2f target_position );
private:
  bool is_in_transition;
};

#endif
