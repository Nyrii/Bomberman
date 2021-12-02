//
// SuddenDeath.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Mon May 30 20:59:26 2016 guillaume wilmot
// Last update Sun Jun  5 08:09:26 2016 Nyrandone Noboud-Inpeng
//

#include "StopSleep.hpp"
#include "SuddenDeath.hpp"
#include "BombManager.hpp"
#include "ClassicBomb.hpp"

void			SuddenDeath::timerSuddenDeath(Map &map, Players &players, ProtectedVar<bool> *end, int nb)
{
  SuddenDeath		sud;

  try {
    StoppableTimer	lock(players.getPlayers().size() * 15, end);
  } catch (const std::exception &) {
    return ;
  }
  sud.setTotalPlayers(nb);
  sud.suddenDeath(sud.getX(), sud.getY(), map, players, end);
  sud.randomBombs(map, players, end, nb);
}

void			SuddenDeath::randomBombs(Map &map, Players &players, ProtectedVar<bool> *end, int nb)
{
  int			nbBombs;
  int			count;
  int			x;
  int			y;
  int			i;

  _totalPlayers = nb;
  while (!end->get())
    {
      i = 0;
      count = map.getMaxX() > map.getMaxY() ? pow(map.getMaxX(), 2) : pow(map.getMaxY(), 2);
      nbBombs = players.getLastPlayers() + 2;
      while (!end->get() && nbBombs > 0)
        {
	    try {
	      StoppableTimer	lock(0.2, end);
	    } catch (const std::exception &) {
	      return ;
	    }
	  if (i == count)
	    break;
          if (!end->get())
	    suddenDeath(_x, _y, map, players, end);
	  if (!end->get())
	    {
	      x = (rand() % (map.getMaxX() - _x)) + _x;
	      y = (rand() % (map.getMaxY() - _y)) + _y;
	      if (!end->get() &&
		  x >= 0 && x < map.getMaxX()
		  && y >= 0 && y < map.getMaxY()
		  && (map.getMap()[y][x]->getItem() == EMPTY
		      || map.getMap()[y][x]->getItem() == BONUS))
		{
		  IBomb		*bomb = new ClassicBomb();

		  bomb->setX(x);
		  bomb->setY(y);
		  map.getMap()[y][x]->setItem(BOMB);
		  map.getDangerMap()[y][x]->setItem(BOMB);
		  BombManager::get().addBomb(map.getMaxX() > map.getMaxY() ? map.getMaxX() : map.getMaxY(), bomb);
		  nbBombs--;
		}
	    }
	  i++;
        }
      try {
        StoppableTimer	lock(4, end);
	} catch (const std::exception &) {
        return ;
      }
    }
}

void			SuddenDeath::suddenDeath(int x, int y, Map &map, Players &players, ProtectedVar<bool> *end)
{
  int			i = 0;
  int			MaxX = map.getMaxX() - x - 1;
  int			MaxY = map.getMaxY() - y - 1;
  int			saveX = 0;
  int			saveY = 0;

  if (end->get() || x < 0 || x >= map.getMaxX() || y < 0 || y >= map.getMaxY()
      || (x == map.getMaxX() - (map.getMaxX() - (_totalPlayers - players.getLastPlayers()) - 2)
       && y == map.getMaxY() - (map.getMaxY() - (_totalPlayers - players.getLastPlayers()) - 2))
      || map.getBeginPerimeter() == 1)
    {
      _x = x;
      _y = y;
      return ;
    }
  for (i = x; i != MaxX && !end->get(); i++)
    map.getDangerMap()[y][i]->setItem(DANGEROUS);
  saveX = i;
  for (i = y; i != MaxY && !end->get(); i++)
    map.getDangerMap()[i][saveX]->setItem(DANGEROUS);
  saveY = i;
  for (i = saveX; i > 0 && i > x && !end->get(); i--)
    map.getDangerMap()[saveY][i]->setItem(DANGEROUS);
  for (i = saveY; i > 0 && i > y && !end->get(); i--)
    map.getDangerMap()[i][x]->setItem(DANGEROUS);
  for (i = x; i != MaxX && !end->get(); i++)
    {
      try {
        StoppableTimer	lock(0.1, end);
      } catch (const std::exception &) {
        return ;
      }
      if (map.getMap()[y][i]->getItem() != BORDER)
	map.getMap()[y][i]->setItem(BORDER);
      map.getDangerMap()[y][i]->setItem(BORDER);
    }
  saveX = i;
  for (i = y; i != MaxY && !end->get(); i++)
    {
      try {
        StoppableTimer	lock(0.1, end);
      } catch (const std::exception &) {
        return ;
      }
      if (map.getMap()[i][saveX]->getItem() != BORDER)
	map.getMap()[i][saveX]->setItem(BORDER);
      map.getDangerMap()[i][saveX]->setItem(BORDER);
    }
  saveY = i;
  for (i = saveX; i > 0 && i > x && !end->get(); i--)
    {
      try {
        StoppableTimer	lock(0.1, end);
      } catch (const std::exception &) {
        return ;
      }
      if (map.getMap()[saveY][i]->getItem() != BORDER)
	map.getMap()[saveY][i]->setItem(BORDER);
      map.getDangerMap()[saveY][i]->setItem(BORDER);
    }
  for (i = saveY; i > 0 && i > y && !end->get(); i--)
    {
      try {
        StoppableTimer	lock(0.1, end);
      } catch (const std::exception &) {
        return ;
      }
      if (map.getMap()[i][x]->getItem() != BORDER)
	map.getMap()[i][x]->setItem(BORDER);
      map.getDangerMap()[i][x]->setItem(BORDER);
    }
  if (!end->get())
    suddenDeath(x + 1, y + 1, map, players, end);
}
