#include <dynamicView.hpp>

using namespace sf;

void DynamicView::update( sf::Vector2f target_position )
{
  Vector2f view_movement(0,0);

  if( ( fabs(getCenter().x - target_position.x) > 600 )
  ||  ( fabs(getCenter().y - target_position.y) > 300 ) )
  {
    is_in_transition = true;
  }

  if( ( fabs(getCenter().x - target_position.x) < 10 )
  &&  ( fabs(getCenter().y - target_position.y) < 10 ) )
  {
    is_in_transition = false;
  }


  if( is_in_transition )
  {
    if( getCenter().x < target_position.x )
        view_movement.x = 10;
    else if ( getCenter().x > target_position.x )
      view_movement.x = -10;

    if( getCenter().y < target_position.y )
      view_movement.y = 10;
    else if ( getCenter().y > target_position.y )
      view_movement.y = -10;
  }

  move(view_movement);

}
