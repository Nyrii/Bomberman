//
// FactoryPowerUps.cpp for FactoryPowerUps in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 17:50:51 2016 Nyrandone Noboud-Inpeng
// Last update Sat Apr 30 20:35:23 2016 Nyrandone Noboud-Inpeng
//

#include "FactoryPowerUps.hh"
#include "RangeUp.hh"
#include "RangeDown.hh"
#include "SpeedUp.hh"
#include "SpeedDown.hh"
#include "Shield.hh"
#include "MoreBomb.hh"

#include <iostream>

FactoryPowerUps::FactoryPowerUps()
{
  _funcPtr[RANGEUP] = &FactoryPowerUps::rangeUp;
  _funcPtr[RANGEDOWN] = &FactoryPowerUps::rangeDown;
  _funcPtr[SPEEDUP] = &FactoryPowerUps::speedUp;
  _funcPtr[SPEEDDOWN] = &FactoryPowerUps::speedDown;
  _funcPtr[SHIELD] = &FactoryPowerUps::shield;
  _funcPtr[MOREBOMB] = &FactoryPowerUps::moreBomb;
}

FactoryPowerUps::~FactoryPowerUps()
{

}

FactoryPowerUps::FactoryPowerUps(FactoryPowerUps const &)
{
}

FactoryPowerUps		&FactoryPowerUps::operator=(FactoryPowerUps const &src)
{
  if (this != &src)
    {
    }
  return (*this);
}

PowerUp			*FactoryPowerUps::createPowerUp(int const x, int const y, Items const &bonus)
{
  if (_funcPtr[bonus])
    return ((this->*_funcPtr[bonus])(x, y));
  return (NULL);
}

PowerUp			*FactoryPowerUps::rangeUp(int const x, int const y) const
{
  return (new RangeUp(x, y));
}

PowerUp			*FactoryPowerUps::rangeDown(int const x, int const y) const
{
  return (new RangeDown(x, y));
}

PowerUp			*FactoryPowerUps::speedUp(int const x, int const y) const
{
  return (new SpeedUp(x, y));
}

PowerUp			*FactoryPowerUps::speedDown(int const x, int const y) const
{
  return (new SpeedDown(x, y));
}

PowerUp			*FactoryPowerUps::shield(int const x, int const y) const
{
  return (new Shield(x, y));
}

PowerUp			*FactoryPowerUps::moreBomb(int const x, int const y) const
{
  return (new MoreBomb(x, y));
}
