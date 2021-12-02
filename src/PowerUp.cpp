//
// PowerUp.cpp for PowerUp in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 16:35:35 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 15:44:33 2016 guillaume wilmot
//

#include "PowerUp.hh"

PowerUp::PowerUp(int const x, int const y)
{
  _posX = x;
  _posY = y;
}

PowerUp::PowerUp(PowerUp const &other)
{
  _posX = other.getPosX();
  _posY = other.getPosY();
}

PowerUp::~PowerUp() {}

PowerUp		&PowerUp::operator=(PowerUp const &other)
{
  if (this != &other)
    {
      _posX = other.getPosX();
      _posY = other.getPosY();
    }
  return *this;
}

int		PowerUp::getPosX() const
{
  return (_posX);
}

int		PowerUp::getPosY() const
{
  return (_posY);
}

irr::scene::IMeshSceneNode	*PowerUp::get3d() const
{
  return (_obj);
}
