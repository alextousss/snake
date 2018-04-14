#include "snake.hpp"

using namespace sf;
using namespace std;

Snake::Snake()
{
  moveByDirection = { Vector2f( 0,-1),
                      Vector2f(-1, 0),
                      Vector2f( 0, 1),
                      Vector2f( 1, 0) };

  coord.push_front( Vector2f(90.f,90.f) );
  quantum = Vector2f(10.f,10.f);
  color = Color(255,70,60);
  size = 15;
  actual_direction = NORTH;
  next_direction = NORTH;
  last_update_timer.restart();
  update_period = UPDATE_PERIOD;
  has_advanced = 0;
  state = 0;
  for( unsigned int i = 0 ; i < 5 ; i++ )
    update();
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
  size = 15;
  actual_direction = NORTH;
  next_direction = NORTH;
  last_update_timer.restart();
  update_period = UPDATE_PERIOD;
  has_advanced = 0;
  state=0;
  for( unsigned int i = 0 ; i < 5 ; i++ )
    update();
}

void Snake::addCoords(std::vector<sf::Vector2f>& coords, unsigned int coords_state)
{
  int local_advance_on_remote = this->state - coords_state;
  if( local_advance_on_remote > 0 )
    for( int i = 0 ; i < local_advance_on_remote ; i++ )
       coord.pop_front();

  for( unsigned int i = 0 ; i < coords.size() ; i++ )
    if( i < coord.size() )
      coord[i] = coords[i];
    else
      coord.push_back(coords[i]);
  state = coords_state;
}


bool Snake::hasAdvanced()
{
  if( has_advanced )
  {
    has_advanced = false;
    return true;
  }
  else return false;
}

void Snake::setDirection( direction_t direction)
{
  if( !( (direction == NORTH && actual_direction == SOUTH)
  ||     (direction == SOUTH && actual_direction == NORTH)
  ||     (direction == EAST  && actual_direction == WEST )
  ||     (direction == WEST  && actual_direction == EAST ) ) )
  {
    this->next_direction = direction;
  }
}

void Snake::update(bool client)
{
  if ( client && last_update_timer.getElapsedTime().asMilliseconds() > update_period )
  {
    coord.push_front( Vector2f(coord[0].x + quantum.x * moveByDirection[ next_direction ].x, coord[0].y + quantum.y * moveByDirection [ next_direction ].y) );
    actual_direction = next_direction;

    has_advanced = true;
    last_update_timer.restart();
    state++;
  }
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
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(vertices);
}
