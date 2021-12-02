//
// Players.cpp for Players in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Wed Apr 27 11:40:43 2016 Nyrandone Noboud-Inpeng
// Last update Tue May 31 14:22:50 2016 Nyrandone Noboud-Inpeng
//

#include <vector>
#include "Players.hh"

Players::Players() {}

Players::~Players() {}

Players			&Players::operator=(Players &src)
{
  if (this != &src)
    _players.set(src.getPlayers());
  return (*this);
}

void			Players::addPlayer(Player * const newPlayer)
{
  _players.get().push_back(newPlayer);
}

void			Players::removePlayer(Player const &) {}

void			Players::setPlayers(std::vector<Player *> const &players)
{
  _players.set(players);
}

std::vector<Player *>	Players::getPlayers()
{
  return (_players.get());
}

int			Players::getLastPlayers()
{
  int			count;

  count = 0;
  for (unsigned int i = 0; i != _players.get().size(); i++)
    {
      if (_players.get()[i]->getAlive() == true)
	++count;
    }
  return (count);
}
