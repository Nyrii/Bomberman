//
// ClassicBomb.cpp for ClassicBomb in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Mon Apr 25 21:50:44 2016 Nyrandone Noboud-Inpeng
// Last update Wed Jun  1 18:47:54 2016 guillaume wilmot
//

#include <chrono>
#include <unistd.h>
#include "ClassicBomb.hpp"
#include "MapError.hpp"
#include "StopSleep.hpp"
#include "ProtectedVar.hpp"
#include "Enum.hh"

ClassicBomb::ClassicBomb()
{
  _detonated = false;
  _detonationDelay = 2;
  _clearDelay = 0.5;
  _range = 2;
}

bool	ClassicBomb::spreadFireUp(Map &map, int const x, int const y, int const i) const
{
  if (x >= map.getMaxX() || x < 0 || y - 1 >= map.getMaxY() || y - i < 0)
    return (true);
  char	item = map.getItem(x, y - i);
  if (item != UNBREAKABLE_WALL && item != BORDER)
    map.addItem(x, y - i, FIRE);
  else
    return (true);
  if (item == BREAKABLE_WALL)
    {
      map.getMap()[y - i][x]->destroy();
      map.addPowerUp(x, y - i);
      return (true);
    }
  return (false);
}

bool	ClassicBomb::spreadFireDown(Map &map, int const x, int const y, int const i) const
{
  if (x >= map.getMaxX() || x < 0 || y + i >= map.getMaxY() || y + i < 0)
    return (true);
  char	item = map.getItem(x, y + i);
  if (item != UNBREAKABLE_WALL && item != BORDER)
    map.addItem(x, y + i, FIRE);
  else
    return (true);
  if (item == BREAKABLE_WALL)
    {
      map.getMap()[y + i][x]->destroy();
      map.addPowerUp(x, y + i);
      return (true);
    }
  return (false);
}

bool	ClassicBomb::spreadFireRight(Map &map, int const x, int const y, int const i) const
{
  if (x + i >= map.getMaxX() || x + i < 0 || y >= map.getMaxY() || y < 0)
    return (true);
  char	item = map.getItem(x + i, y);
  if (item != UNBREAKABLE_WALL && item != BORDER)
    map.addItem(x + i, y, FIRE);
  else
    return (true);
  if (item == BREAKABLE_WALL)
    {
      map.getMap()[y][x + i]->destroy();
      map.addPowerUp(x + i, y);
      return (true);
    }
  return (false);
}

bool	ClassicBomb::spreadFireLeft(Map &map, int const x, int const y, int const i) const
{
  if (x - i >= map.getMaxX() || x - i < 0 || y >= map.getMaxY() || y < 0)
    return (true);
  char	item = map.getItem(x - i, y);
  if (item != UNBREAKABLE_WALL && item != BORDER)
    map.addItem(x - i, y, FIRE);
  else
    return (true);
  if (item == BREAKABLE_WALL)
    {
      map.getMap()[y][x - i]->destroy();
      map.addPowerUp(x - i, y);
      return (true);
    }
  return (false);
}

void	ClassicBomb::clearFireUp(Map &map, int const x, int const y, int const i) const
{
  if (x >= map.getMaxX() || x < 0 || y - i >= map.getMaxY() || y - i < 0)
    return ;
  if (map.getItem(x, y - i) == FIRE)
    map.addItem(x, y - i, EMPTY);
}

void	ClassicBomb::clearFireDown(Map &map, int const x, int const y, int const i) const
{
  if (x >= map.getMaxX() || x < 0 || y + i >= map.getMaxY() || y + i < 0)
    return ;
  if (map.getItem(x, y + i) == FIRE)
    map.addItem(x, y + i, EMPTY);
}

void	ClassicBomb::clearFireRight(Map &map, int const x, int const y, int const i) const
{
  if (x + i >= map.getMaxX() || x + i < 0 || y >= map.getMaxY() || y < 0)
    return ;
  if (map.getItem(x + i, y) == FIRE)
    map.addItem(x + i, y, EMPTY);
}

void	ClassicBomb::clearFireLeft(Map &map, int const x, int const y, int const i) const
{
  if (x - i >= map.getMaxX() || x - i < 0 || y >= map.getMaxY() || y < 0)
    return ;
  if (map.getItem(x - i, y) == FIRE)
    map.addItem(x - i, y, EMPTY);
}
