//
// IA.cpp for IA in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Mon Apr 25 22:33:20 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 21:46:31 2016 Nyrandone Noboud-Inpeng
//

#include <cmath>
#include <algorithm>
#include <unistd.h>
#include "IA.hh"
#include "StopSleep.hpp"
#include "PathFinding.hh"
#include "Lagrange.hh"
#include "chaiscript.hpp"
#include "chaiscript_stdlib.hpp"
#include "Displayer.hpp"
#include "Sdl.hpp"

IA::IA(int const id, double const x, double const y,
       t_user *u_settings, std::vector<std::string> &skinList) : Player(id, x, y, u_settings, skinList)
{
  int			random = rand() % 4;
  std::map<int, void (IA::*)()>	functionPtr;

  _human = false;
  _done = true;

  functionPtr[0] = &IA::initAttacker;
  functionPtr[1] = &IA::initCollector;
  functionPtr[2] = &IA::initDestroyer;
  functionPtr[3] = &IA::initRunner;

  if (functionPtr[random])
    (this->*functionPtr[random])();
}

IA::~IA()
{}

Map				IA::getMap() const
{
  return (_map);
}

std::map<Modules, int>		IA::getTemplateCoeff() const
{
  return (_templateCoeff);
}

std::map<Modules, int>		IA::getTmpCoeff() const
{
  return (_tmpCoeff);
}

std::map<Modules, t_infos>	IA::getModuleStates() const
{
  return (_moduleStates);
}

std::vector<std::vector<Tile *>>	IA::getPositionMap() const
{
  return (_positionMap);
}

std::vector<std::vector<Tile *>>	IA::getDirectionMap() const
{
  return (_directionMap);
}

void		IA::initAttacker()
{
  _templateCoeff[PLAYERS] = 50;
  _templateCoeff[BONUS] = 40;
  _templateCoeff[BREAKWALL] = 20;
  _templateCoeff[RUN] = 1;
}

void		IA::initCollector()
{
  _templateCoeff[PLAYERS] = 35;
  _templateCoeff[BONUS] = 60;
  _templateCoeff[BREAKWALL] = 40;
  _templateCoeff[RUN] = 1;
}

void		IA::initRunner()
{
  _templateCoeff[PLAYERS] = 20;
  _templateCoeff[BONUS] = 50;
  _templateCoeff[BREAKWALL] = 30;
  _templateCoeff[RUN] = 10;
}

void		IA::initDestroyer()
{
  _templateCoeff[PLAYERS] = 50;
  _templateCoeff[BONUS] = 40;
  _templateCoeff[BREAKWALL] = 40;
  _templateCoeff[RUN] = 5;
}

void		IA::setTmpCoefficients()
{
  _tmpCoeff[PLAYERS] = _templateCoeff[PLAYERS];
  _tmpCoeff[BONUS] = _templateCoeff[BONUS];
  _tmpCoeff[BREAKWALL] = _templateCoeff[BREAKWALL];
  _tmpCoeff[RUN] = _templateCoeff[RUN];
}

void		IA::stayAwayFromOthers(Map &map, Players &playersList)
{
  t_infos	infos;

  infos.x = -1;
  infos.y = -1;
  infos.distance = 0;
  infos.dir = runAway(map, playersList, 1);
  checkAndSetDirection(infos, map, playersList, RUN);
  _moduleStates[RUN] = infos;
}

bool		IA::simulatePlaceBomb(Map &map, Players &players, int const x, int const y)
{
  IBomb		*bomb = getNextBomb();
  if (!bomb)
    return (false);
  int		bombRange = bomb->getRange() + _rangeBonus.get();
  Direction	ret_value;

  simulateFire(map, x, y, bombRange);
  if ((ret_value = runAway(map, players, 1)) == UNDEFINED || ret_value == NONE)
    return (false);
  return (true);
}

void		IA::simulateFire(Map &map, int const x, int const y, int const bombRange) const
{
  int		tmpx, tmpy;
  int		addX = 0;
  int		addY = 0;

  for (int i = 0; i < 4; ++i)
    {
      switch (i)
	{
	case 0:
	  addX = 0;
	  addY = -1;
	  break;
	case 1:
	  addX = 0;
	  addY = 1;
	  break;
	case 2:
	  addX = 1;
	  addY = 0;
	  break;
	case 3:
	  addX= -1;
	  addY = 0;
	  break;
	}
      tmpx = x;
      tmpy = y;
      for (int j = 0; j <= bombRange; ++j)
	{
	  if (tmpx > 0 && tmpy > 0 && tmpx < map.getMaxX() && tmpy < map.getMaxY()
	      && map.getDangerMap()[tmpy][tmpx]->getItem() == EMPTY)
	    map.getDangerMap()[tmpy][tmpx]->setItem(SIMULATIONDANGER);
	  tmpx += addX;
	  tmpy += addY;
	}
    }
}

void		IA::removeSimulation(Map &map) const
{
  for (unsigned int y = 0; y < map.getDangerMap().size(); y++)
    for (unsigned int x = 0; x < map.getDangerMap()[y].size(); x++)
      if (map.getDangerMap()[y][x]->getItem() == SIMULATIONDANGER)
	map.getDangerMap()[y][x]->setItem(EMPTY);
}

bool			IA::NearDistance(t_infos const &first, t_infos const &second)
{
  return (first.distance < second.distance);
}

Direction		IA::runAway(Map &map, Players &players, bool const simulation)
{
  int			min = -1;
  t_infos		infos;
  PathFinding		findWay;
  std::vector<t_infos>	posVector;

  if (map.getDangerMap()[floor(_posY.get())][floor(_posX.get())]->getItem() == EMPTY
      && (map.getDangerMap()[floor(_posY.get()) - 1][floor(_posX.get())]->getItem() == DANGEROUS
	  || map.getDangerMap()[floor(_posY.get()) - 1][floor(_posX.get())]->getItem() == SIMULATIONDANGER)
      && (map.getDangerMap()[floor(_posY.get()) + 1][floor(_posX.get())]->getItem() == DANGEROUS
	  || map.getDangerMap()[floor(_posY.get()) + 1][floor(_posX.get())]->getItem() == SIMULATIONDANGER)
      && (map.getDangerMap()[floor(_posY.get())][floor(_posX.get()) - 1]->getItem() == DANGEROUS
	  || map.getDangerMap()[floor(_posY.get())][floor(_posX.get()) - 1]->getItem() == SIMULATIONDANGER)
      && (map.getDangerMap()[floor(_posY.get())][floor(_posX.get()) + 1]->getItem() == DANGEROUS
	  || map.getDangerMap()[floor(_posY.get())][floor(_posX.get()) + 1]->getItem() == SIMULATIONDANGER))
    {
      removeSimulation(map);
      if (simulation == false)
	{
	  _curDirection = NONE;
	  _done = true;
	  _oldPos[0] = _posY.get();
	  _oldPos[1] = _posX.get();
	  reOrient();
	}
      return (NONE);
    }
  for (unsigned int y = 1; y != map.getDangerMap().size() - 1; y++)
    for (unsigned int x = 1; x != map.getDangerMap()[y].size() - 1; x++)
      if (map.getDangerMap()[y][x]->getItem() == EMPTY)
	{
	  infos.x = x;
	  infos.y = y;
	  infos.distance = std::abs(x - floor(_posX.get())) + std::abs(y - floor(_posY.get()));
	  if (infos.distance < 4)
	    posVector.push_back(infos);
	}
  std::sort(posVector.begin(), posVector.end(), &IA::NearDistance);
  for (unsigned int i = 0; i != posVector.size(); i++)
    if (map.getDangerMap()[posVector[i].y][posVector[i].x]->getItem() == EMPTY)
      {
	infos.x = posVector[i].x;
	infos.y = posVector[i].y;
	infos.distance = posVector[i].distance;
	infos.dir = UNDEFINED;
	findWay.processPaths(map, -1, -1, players);
	infos.dir = static_cast<Direction>(findWay.findBestWay(floor(_posX.get()), floor(_posY.get()), infos));
	if ((infos.dir == UP && map.isAnObstacle(floor(_posX.get()), floor(_posY.get()) - 1, players))
	    || (infos.dir == DOWN && map.isAnObstacle(floor(_posX.get()), floor(_posY.get()) + 1, players))
	    || (infos.dir == RIGHT && map.isAnObstacle(floor(_posX.get()) + 1, floor(_posY.get()), players))
	    || (infos.dir == LEFT && map.isAnObstacle(floor(_posX.get()) - 1, floor(_posY.get()), players)))
	  infos.dir = NONE;
	findWay.freePaths();
	if (infos.dir != UNDEFINED && infos.dir != NONE
	    && map.getDangerMap()[posVector[i].y][posVector[i].x]->getItem() == EMPTY)
	  {
	    removeSimulation(map);
	    if (simulation == false)
	      {
		_curDirection = infos.dir;
		_done = false;
		_oldPos[0] = _posY.get();
		_oldPos[1] = _posX.get();
		reOrient();
	      }
	    posVector.clear();
	    return (infos.dir);
	  }
      }
  removeSimulation(map);
  if (simulation == false)
    {
      _curDirection = NONE;
      _steve->playAnim("idle");
    }
  return (NONE);
}

void		IA::simulateDanger(Map &map)
{
  for (int i = 0; i < map.getMaxY(); ++i)
    for (int j = 0; j < map.getMaxX(); ++j)
      if (map.getMap()[i][j]->getItem() == BOMB)
	simulateFire(map, j, i, _rangeBonus.get() + 2);
}

bool		IA::isInDanger(Map &map, int const x, int const y)
{
  for (int i = 0; i < map.getMaxY(); ++i)
    for (int j = 0; j < map.getMaxX(); ++j)
      if (map.getMap()[i][j]->getItem() == BOMB)
	simulateFire(map, j, i, _rangeBonus.get() + 2);
  if (map.getDangerMap()[y][x]->getItem() == DANGEROUS
      || map.getDangerMap()[y][x]->getItem() == SIMULATIONDANGER)
    {
      removeSimulation(map);
      return true;
    }
  removeSimulation(map);
  return false;
}

Player		*IA::getPlayer()
{
  return (this);
}

void		IA::play(Map &map, Players &players, ProtectedVar<bool> *start, ProtectedVar<bool> *end)
{
  PathFinding	findWay;
  bool		winner = false;

  chaiscript::ChaiScript	chai(chaiscript::Std_Lib::library());

  chai.add(chaiscript::var(findWay), "findWay");
  chai.add(chaiscript::var(&map), "map");
  chai.add(chaiscript::fun(&Map::getMaxX), "getMaxX");
  chai.add(chaiscript::fun(&Map::getMaxY), "getMaxY");
  chai.add(chaiscript::var(&players), "players");
  chai.add(chaiscript::var(this), "ia");
  chai.add(chaiscript::var(&_posX), "_posX");
  chai.add(chaiscript::var(&_posY), "_posY");
  chai.add(chaiscript::fun(&IA::getPlayer), "getPlayer");
  chai.add(chaiscript::fun(&IA::setTmpCoefficients), "setTmpCoefficients");
  chai.add(chaiscript::fun(&IA::isInDanger), "isInDanger");
  chai.add(chaiscript::fun(&IA::runAway), "runAway");
  chai.add(chaiscript::fun(&IA::breakWalls), "breakWalls");
  chai.add(chaiscript::fun(&IA::findPlayers), "findPlayers");
  chai.add(chaiscript::fun(&IA::stayAwayFromOthers), "stayAwayFromOthers");
  chai.add(chaiscript::fun(&IA::findBonus), "findBonus");
  chai.add(chaiscript::fun(&IA::calculWeight), "calculWeight");
  chai.add(chaiscript::fun(&IA::findBestAction), "findBestAction");
  chai.add(chaiscript::fun(&ProtectedVar<double>::get), "getVariable");
  chai.add(chaiscript::fun(&floor), "floor");
  chai.add(chaiscript::fun(&pow), "pow");
  chai.add(chaiscript::fun(&sqrt), "sqrt");

  _end = end;
  while (!_end->get())
    {
      while (!start->get());
      if (isWinner(players))
	{
	  winner = true;
	  break ;
	}
      if (isDead(map))
	{
          SDL::get().playSound(DEATH);
	  setAlive(false);
          _curDirection = UNDEFINED;
	  _steve->playAnim("die");
	  try {StoppableTimer t(0.5, end);} catch (const std::exception &) {}
          break;
        }
      map.compareBonusAndPlayerPos(*this);
      if (!_done)
	{
	  try {
	    StoppableTimer	timer(0.05, _end);
	  } catch (const std::exception &) {
	    return ;
	  }
	}
      else
	{
	  try
	    {
	      chai.eval_file("./script/ia.chai");
	    } catch (const chaiscript::exception::eval_error &e) {
	      std::cout << e.pretty_print() << std::endl;
	      return ;
	    } catch (const chaiscript::exception::file_not_found_error &e)
	    {
	      std::cout << e.what() << std::endl;
	      return ;
	    }
	}
    }
  if (_end->get())
    return ;
  if (winner == true)
    {
      std::cout << _id << " WIN !" << std::endl;
      _end->set(true);
    }
  else
    {
      std::cout << _id << " LOOSE !" << std::endl;
      _steve->playAnim("die");
      try {StoppableTimer t(0.5, end);} catch (const std::exception &) {}
      setAlive(false);
      Displayer::getSmgrMutex().lock();
      _steve->getBlock()->remove();
      Displayer::getSmgrMutex().unlock();
    }
}

void		IA::findBestAction(Map &map, Players &players)
{
  Modules	tmp = RUN;
  int		best = 0;
  static int	i = 0;

  for (std::map<Modules, int>::iterator it = _tmpCoeff.begin(); it != _tmpCoeff.end(); ++it)
    {
      if (it->second > best)
	{
	  best = it->second;
	  tmp = it->first;
	}
    }
  if (tmp == PLAYERS || tmp == BREAKWALL)
    {
      if (_moduleStates[tmp].dir == NONE
	  && simulatePlaceBomb(map, players, floor(_posX.get()), floor(_posY.get())))
	{
	  _curDirection = NONE;
	  _steve->playAnim("idle");
	  PlaceBomb(map);
	}
      else if ((_curDirection = _moduleStates[tmp].dir) != NONE && _curDirection != UNDEFINED)
	{
	  _done = false;
	  _oldPos[0] = _posY.get();
	  _oldPos[1] = _posX.get();
	  reOrient();
	}
      else
	_steve->playAnim("idle");
    }
  else if ((_curDirection = _moduleStates[tmp].dir) != NONE && _curDirection != UNDEFINED)
    {
      _done = false;
      _oldPos[0] = _posY.get();
      _oldPos[1] = _posX.get();
      reOrient();
    }
  else
    _steve->playAnim("idle");
}

void		IA::calculWeight(int distanceMax)
{
  Lagrange	algorithm;

  for (std::map<Modules, int>::iterator it = _tmpCoeff.begin(); it != _tmpCoeff.end(); ++it)
    {
      if (_moduleStates[it->first].dir == UNDEFINED || _moduleStates[it->first].distance == -1)
	_tmpCoeff[it->first] = 0;
      else
	{
	  _tmpCoeff[it->first] -= floor(algorithm.lagrange(_moduleStates[it->first].distance,
							   distanceMax, _templateCoeff[it->first]));
	}
    }
}

void		IA::findBonus(Map &map, PathFinding &findWay, Players &players)
{
  int		save_x = -1;
  int		save_y = -1;
  int		min = -1;
  t_infos	infos;

  for (unsigned int y = 0; y != map.getMap().size(); y++)
    {
      for (unsigned int x = 0; x != map.getMap()[y].size(); x++)
	{
	  if (map.getMap()[y][x]->getItem() == RANGEUP
	      || map.getMap()[y][x]->getItem() == SPEEDUP
	      || map.getMap()[y][x]->getItem() == SHIELD
	      || map.getMap()[y][x]->getItem() == MOREBOMB)
	    {
	      if (std::abs(x - floor(_posX.get())) + std::abs(y - floor(_posY.get())) < min
		  || min == -1)
		{
		  min = std::abs(x - floor(_posX.get())) + std::abs(y - floor(_posY.get()));
		  save_x = x;
		  save_y = y;
		}
	    }
	}
    }
  infos.x = save_x;
  infos.y = save_y;
  infos.distance = 0;
  infos.dir = UNDEFINED;
  _moduleStates[BONUS] = infos;
  if (save_x == -1 || save_y == -1)
    {
      infos.distance = -1;
      _moduleStates[BONUS] = infos;
      return ;
    }
  if (infos.x == floor(_posX.get()) && infos.y == floor(_posY.get()))
    return ;
  findWay.processPaths(map, -1, -1, players);
  infos.dir = static_cast<Direction>(findWay.findBestWay(floor(_posX.get()), floor(_posY.get()), infos));
  checkAndSetDirection(infos, map, players, BONUS);
  ++infos.distance;
  _moduleStates[BONUS] = infos;
  findWay.freePaths();
}

void		IA::findPlayers(Map &map, PathFinding &findWay, Players &players)
{
  int		save_x = -1;
  int		save_y = -1;
  int		min = -1;
  Player	*savePlayer = NULL;
  t_infos	infos;

  for (unsigned int i = 0; i != players.getPlayers().size(); i++)
    {
      int	x = floor(players.getPlayers()[i]->getPosX());
      int	y = floor(players.getPlayers()[i]->getPosY());
      if (players.getPlayers()[i]->getAlive() == true)
	{
	  if ((std::abs(x - floor(_posX.get())) + std::abs(y - floor(_posY.get())) < min || min == -1)
	      && (x != floor(_posX.get()) || y != floor(_posY.get())))
	    {
	      min = std::abs(x - floor(_posX.get())) + std::abs(y - floor(_posY.get()));
	      save_x = x;
	      save_y = y;
	      savePlayer = players.getPlayers()[i];
	    }
	}
    }
  infos.x = save_x;
  infos.y = save_y;
  infos.distance = 0;
  infos.dir = UNDEFINED;
  if (save_x == -1 || save_y == -1 || savePlayer == NULL)
    {
      infos.distance = -1;
      _moduleStates[PLAYERS] = infos;
      return ;
    }
  findWay.processPaths(map, infos.x, infos.y, players);
  infos.dir = static_cast<Direction>(findWay.findBestWay(floor(_posX.get()), floor(_posY.get()), infos));
  if (isInRange(infos, map, PLAYER, savePlayer))
    {
      infos.dir = NONE;
      infos.distance = 0;
    }
  checkAndSetDirection(infos, map, players, PLAYERS);
  _moduleStates[PLAYERS] = infos;
  findWay.freePaths();
}

void		IA::breakWalls(Map &map, PathFinding &findWay, Players &players)
{
  int		save_x = -1;
  int		save_y = -1;
  int		min = -1;
  t_infos	infos;

  for (unsigned int y = 0; y != map.getMap().size(); y++)
    {
      for (unsigned int x = 0; x != map.getMap()[y].size(); x++)
	{
	  if (map.getMap()[y][x]->getItem() == BREAKABLE_WALL)
	    {
	      if (std::abs(x - floor(_posX.get())) + std::abs(y - floor(_posY.get())) < min
		  || min == -1)
		{
		  min = std::abs(x - floor(_posX.get())) + std::abs(y - floor(_posY.get()));
                  save_x = x;
                  save_y = y;
		}
	    }
	}
    }
  infos.x = save_x;
  infos.y = save_y;
  infos.distance = 0;
  infos.dir = UNDEFINED;
  if (save_x == -1 || save_y == -1)
    {
      infos.distance = -1;
      _moduleStates[BREAKWALL] = infos;
      return ;
    }
  findWay.processPaths(map, infos.x, infos.y, players);
  infos.dir = static_cast<Direction>(findWay.findBestWay(floor(_posX.get()), floor(_posY.get()), infos));
  checkAndSetDirection(infos, map, players, BREAKWALL);
  _moduleStates[BREAKWALL] = infos;
  findWay.freePaths();
}

bool		IA::isInRange(t_infos const &infos, Map &map,
			      Items const &item, Player *player)
{
  int		k = 0;
  int		range = 0;
  IBomb		*nextBomb = getNextBomb();

  if (infos.x == floor(_posX.get()))
    {
      for (k = floor(_posY.get()); k > 0 && k < floor(player->getPosY())
	   && map.getMap()[k][infos.x]->getItem() != UNBREAKABLE_WALL
	   && map.getMap()[k][infos.x]->getItem() != BORDER
	   && map.getMap()[k][infos.x]->getItem() != BREAKABLE_WALL; k--)
	++range;
      if (infos.y == k && nextBomb
	  && nextBomb->getRange() + _rangeBonus.get() >= range)
	return (true);
      else if (infos.x >= 0 && infos.x < map.getMaxX())
	{
	  range = 0;
	  for (k = floor(_posY.get()); k < map.getMaxY() && k < floor(player->getPosY())
	       && map.getMap()[k][infos.x]->getItem() != UNBREAKABLE_WALL
	       && map.getMap()[k][infos.x]->getItem() != BORDER
	       && map.getMap()[k][infos.x]->getItem() != BREAKABLE_WALL; k++)
	    ++range;
	  if (k < map.getMaxY() && infos.y == k && nextBomb
	      && nextBomb->getRange() + _rangeBonus.get() >= range)
	    return (true);
	}
    }
  else if (infos.y == floor(_posY.get()))
    {
      range = 0;
      for (k = floor(_posX.get()); k > 0 && k < floor(player->getPosX())
	   && map.getMap()[infos.y][k]->getItem() != UNBREAKABLE_WALL
	   && map.getMap()[infos.y][k]->getItem() != BORDER
	   && map.getMap()[infos.y][k]->getItem() != BREAKABLE_WALL; k--)
	++range;
      if (k == infos.x && nextBomb
	  && nextBomb->getRange() + _rangeBonus.get() >= range)
	return (true);
      else if (infos.y >= 0 && infos.y < map.getMaxY())
	{
	  range = 0;
	  for (k = floor(_posX.get()); k < map.getMaxX() && k < floor(player->getPosX())
	       && map.getMap()[infos.y][k]->getItem() != UNBREAKABLE_WALL
	       && map.getMap()[infos.y][k]->getItem() != BORDER
	       && map.getMap()[infos.y][k]->getItem() != BREAKABLE_WALL; k++)
	    ++range;
	  if (k < map.getMaxX() && k == infos.x && nextBomb
	      && nextBomb->getRange() + _rangeBonus.get() >= range)
	    return (true);
	}
    }
  return (false);
}

void		IA::checkAndSetDirection(t_infos &infos, Map &map, Players &players, Modules const mod)
{
  simulateDanger(map);
  if ((infos.dir == UP && (map.isAnObstacle(floor(_posX.get()), floor(_posY.get()) - 1, players)
			   || map.getDangerMap()[floor(_posY.get()) - 1][floor(_posX.get())]->getItem() == DANGEROUS
			   || map.getDangerMap()[floor(_posY.get()) - 1][floor(_posX.get())]->getItem() == SIMULATIONDANGER))
      || (infos.dir == DOWN && (map.isAnObstacle(floor(_posX.get()), floor(_posY.get()) + 1, players)
				|| map.getDangerMap()[floor(_posY.get()) + 1][floor(_posX.get())]->getItem() == DANGEROUS
				|| map.getDangerMap()[floor(_posY.get()) + 1][floor(_posX.get())]->getItem() == SIMULATIONDANGER))
      || (infos.dir == RIGHT && (map.isAnObstacle(floor(_posX.get()) + 1, floor(_posY.get()), players)
				 || map.getDangerMap()[floor(_posY.get())][floor(_posX.get()) + 1]->getItem() == DANGEROUS
				 || map.getDangerMap()[floor(_posY.get())][floor(_posX.get()) + 1]->getItem() == SIMULATIONDANGER))
      || (infos.dir == LEFT && (map.isAnObstacle(floor(_posX.get()) - 1, floor(_posY.get()), players)
				|| map.getDangerMap()[floor(_posY.get())][floor(_posX.get()) - 1]->getItem() == DANGEROUS
				|| map.getDangerMap()[floor(_posY.get())][floor(_posX.get()) - 1]->getItem() == SIMULATIONDANGER)))
    {
      if (mod == PLAYERS)
	infos.dir = UNDEFINED;
      else
	infos.dir = NONE;
    }
  removeSimulation(map);
}
