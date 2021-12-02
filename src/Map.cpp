//
// Map.cpp for map in /home/milcen_a/C++/cpp_indie_studio
//
// Made by
// Login   <milcen_a@epitech.net>
//
// Started on  Mon Apr 25 21:32:34 2016
// Last update Sun Jun  5 16:58:27 2016 guillaume wilmot
//

#include <cstdlib>
#include <cmath>
#include "Map.hh"
#include "MapError.hpp"
#include "Enum.hh"
#include "Players.hh"
#include "IA.hh"
#include "FactoryPowerUps.hh"
#include "ScopedLock.hpp"
#include "Displayer.hpp"
#include "CMeshCombiner.hh"
#include "Sdl.hpp"

Map::Map()
{
  _index = 0;
  _maxX = 0;
  _maxY = 0;
  _minPowerUp = 'a';
  _maxPowerUp = 'f';
  _maxRandVal = _maxPowerUp + (_maxPowerUp - _minPowerUp);
}

Map::~Map() {}

int					Map::getBeginPerimeter() const
{
  return (_beginPerimeter);
}

std::vector<std::vector<Tile *>>	&Map::getMap()
{
  return (_map);
}

std::vector<std::vector<Tile *>>	&Map::getDangerMap()
{
  return (_dangerMap);
}

std::vector<std::vector<Tile *>>	Map::copyMap()
{
  std::vector<Tile *>			tmpStorage;
  std::vector<std::vector<Tile *>>	tmp;

  for (int y = 0; y < _maxY; y++)
    {
      for (int x = 0; x < _maxX; x++)
	tmpStorage.push_back(new Tile((*_map[y][x]).getItem(), y, x));
      tmp.push_back(tmpStorage);
      tmpStorage.clear();
    }
  return (tmp);
}

char				Map::getItem(int const x, int const y)
{
  return (_map[y][x]->getItem());
}

int				Map::getMaxX() const
{
  return _maxX;
}

int				Map::getMaxY() const
{
  return _maxY;
}

void				Map::setMap(std::vector<std::vector<Tile *>> const &newMap)
{
  _map = newMap;
}

void				Map::generate(int nbIA, int nbNormal, Players &roster,
					      std::vector<t_user *> &u_settings)
{
  int				size = (nbIA + nbNormal) * 2 + 5;
  int				nbPlayers = (nbIA + nbNormal);
  int				id = 0;
  std::vector<std::string>	skinList;

  if (nbPlayers <= 1)
    throw MapError("Error : invalid players number (nbPlayers <= 1).");
  _nbPlayers = (nbIA + nbNormal);
  _maxX = size;
  _maxY = size;
  _beginPerimeter = 1;
  _endPerimeter = size % 2 == 0 ? size - 1 : size - 2;
  if (size % 2 == 0)
    {
      ++_maxX;
      ++_maxY;
    }
  for (unsigned int i = 0; i != u_settings.size(); ++i)
    {
      if (u_settings[i] != NULL && u_settings[i]->status == true)
	skinList.push_back(u_settings[i]->skin);
    }
  placeFirstPlayers(nbPlayers, id, nbIA, nbNormal, roster, u_settings, skinList);
  placeOtherPlayers(nbPlayers, id, nbIA, nbNormal, roster, u_settings, skinList);
  setFinalMap(roster);
}

void				Map::placeFirstPlayers(int &nbPlayers, int &id,
						       int &nbIA, int &nbNormal, Players &roster,
						       std::vector<t_user *> &u_settings,
						       std::vector<std::string> &skinList)
{
  int				random = 0;
  std::vector<Tile *>		row(_maxX);
  irr::scene::ISceneManager	*smgr = Displayer::getSmgr();

  for (int yPos = 0; yPos < _maxY; ++yPos)
    {
      row.clear();
      for (int xPos = 0; xPos < _maxX; ++xPos)
	{
      	  if (yPos == 0 || xPos == 0 || yPos + 1 == _maxY || xPos + 1 == _maxX)
	    row.push_back(new Tile(BORDER, yPos, xPos));
	  else if (yPos % 2 == 0 && xPos % 2 == 0)
	    row.push_back(new Tile(UNBREAKABLE_WALL, yPos, xPos));
	  else if (nbPlayers > 0
		   && ((yPos == _beginPerimeter && xPos == _beginPerimeter)
		       || (yPos == _beginPerimeter && xPos == _endPerimeter)
		       || (yPos == _endPerimeter && xPos == _beginPerimeter)
		       || (yPos == _endPerimeter && xPos == _endPerimeter)))
	    {
	      random = rand() % 2;
	      if ((random == 0 && nbIA > 0) || nbNormal == 0)
		{
		  roster.addPlayer(new IA(id++, xPos, yPos, NULL, skinList));
		  --nbIA;
		}
	      else
		{
		  roster.addPlayer(new Player(id++, xPos, yPos, u_settings[_index++], skinList));
		  --nbNormal;
		}
	      nbPlayers -= 1;
              row.push_back(new Tile(BREAKABLE_WALL, yPos, xPos));
	    }
	  else
	    row.push_back(new Tile(BREAKABLE_WALL, yPos, xPos));
	}
      if (nbPlayers > 0 && _nbPlayers >= 5 && _nbPlayers % 2 == 1 && yPos == _maxY / 2)
	{
	  random = rand() % 2;
	  if ((random == 0 && nbIA > 0) || nbNormal == 0)
	    {
	      roster.addPlayer(new IA(id++, _maxX / 2, yPos, NULL, skinList));
	      --nbIA;
	    }
	  else
	    {
	      roster.addPlayer(new Player(id++, _maxX / 2, yPos, u_settings[_index++], skinList));
	      --nbNormal;
	    }
	  nbPlayers -= 1;
	}
      _map.push_back(row);
    }
}

void				Map::placeOtherPlayers(int &nbPlayers, int &id,
						       int &nbIA, int &nbNormal,
						       Players &roster, std::vector<t_user *> &u_settings,
						       std::vector<std::string> &skinList)
{
  int				random = 0;

  _beginPerimeter += 4;
  _endPerimeter -= 4;
  while (nbPlayers > 0)
    {
      for (int yPos = 0; yPos != _maxY && nbPlayers > 0; yPos++)
	{
	  for (int xPos = 0; xPos != _maxX && nbPlayers > 0; xPos++)
	    {
	      if (nbPlayers > 0
		  && ((yPos == _beginPerimeter && xPos == _beginPerimeter)
		      || (yPos == _beginPerimeter && xPos == _endPerimeter)
		      || (yPos == _endPerimeter && xPos == _beginPerimeter)
		      || (yPos == _endPerimeter && xPos == _endPerimeter)))
		{
		  random = rand() % 2;
		  if ((random == 0 && nbIA > 0) || nbNormal == 0)
		    {
		      roster.addPlayer(new IA(id++, xPos, yPos, NULL, skinList));
		      --nbIA;
		    }
		  else
		    {
		      roster.addPlayer(new Player(id++, xPos, yPos, u_settings[_index++], skinList));
		      --nbNormal;
		    }
		  nbPlayers -= 1;
		}
	    }
      }
    }
  _beginPerimeter += 4;
  _endPerimeter -= 4;
}

void				Map::setFinalMap(Players &roster)
{
  irr::core::array<irr::scene::IMeshSceneNode *> nodes;
  double			y;
  double			x;
  irr::scene::ISceneManager	*smgr = Displayer::getSmgr();
  CMeshCombiner			combiner;
  char				item;
  irr::scene::IMesh		*combined;
  irr::scene::IMeshSceneNode	*mesh;

  for (unsigned i = 0; i != roster.getPlayers().size(); i++)
    {
      y = roster.getPlayers()[i]->getPosY();
      x = roster.getPlayers()[i]->getPosX();
      _map[y][x]->setItem(EMPTY);
      _map[y][x - 1]->getItem() == BREAKABLE_WALL ? _map[y][x - 1]->setItem(EMPTY) : static_cast<void>(_map);
      _map[y - 1][x]->getItem() == BREAKABLE_WALL ? _map[y - 1][x]->setItem(EMPTY) : static_cast<void>(_map);
      _map[y][x + 1]->getItem() == BREAKABLE_WALL ? _map[y][x + 1]->setItem(EMPTY) : static_cast<void>(_map);
      _map[y + 1][x]->getItem() == BREAKABLE_WALL ? _map[y + 1][x]->setItem(EMPTY) : static_cast<void>(_map);
    }
  _fireMgr.get().init(_map);
  for (y = 0; y < _maxY; y++)
    {
      _dangerMap.push_back(std::vector<Tile *> (0));
      for (x = 0; x < _maxX; x++)
	{
	  _dangerMap[y].push_back(new Tile(_map[y][x]->getItem(), y, x));
	  _map[y][x]->init(smgr);
	  if (_map[y][x]->getItem() == UNBREAKABLE_WALL || _map[y][x]->getItem() == BORDER)
	    if (_map[y][x]->getWall())
	      nodes.push_back(_map[y][x]->getWall()->getBlock());
	  nodes.push_back(_map[y][x]->getGround()->getBlock());
	}
    }
  combined = combiner.combineMeshes(smgr, nodes, "Scene", true, false);
  if (!(mesh = smgr->addMeshSceneNode(combined)))
    throw MapError("Could not merge geometry");
  mesh->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
  mesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
}

void				Map::destroyPos(const unsigned int x, const unsigned int y)
{
  if (_map[y][x]->getItem() != UNBREAKABLE_WALL)
    _map[y][x]->setItem(EMPTY);
}

void				Map::addItem(const unsigned int x, const unsigned int y, Items const &item)
{
  if (x >= _maxX || y >= _maxY)
    return ;
  if (item == FIRE)
    {
      deletePowerup(x, y);
      _fireMgr.get().putFire(x, y);
      _map[y][x]->setFirePower(_map[y][x]->getFirePower() + 1);
      _map[y][x]->setItem(item);
    }
  else
    {
      if (_map[y][x]->getFirePower() > 1)
	_map[y][x]->setFirePower(_map[y][x]->getFirePower() - 1);
      else
	{
	  _fireMgr.get().removeFire(x, y);
	  _map[y][x]->setFirePower(0);
	  _map[y][x]->setItem(item);
	}
    }
}

void				Map::addPowerUp(const int x, const int y)
{
  PowerUp			*tmp;
  FactoryPowerUps		factory;
  int				randVal;

  if (x >= _maxX || x < 0 || y >= _maxY || y < 0)
    return ;
  randVal = rand() % (((_maxRandVal + 1) - _minPowerUp) * 2) + _minPowerUp;
  if (randVal >= _minPowerUp && randVal <= _maxPowerUp)
    {
      if ((tmp = factory.createPowerUp(x, y, static_cast<Items>(randVal))) == NULL)
	return ;
      try {tmp->createItem();} catch (const MapError &e) {return ;}
      irr::scene::IMeshSceneNode	*item;
      if (!(item = tmp->get3d()))
	return ;
      item->setPosition(irr::core::vector3df((x + 0.5) * SCALE_GAME, SCALE_GAME / 2, (y + 0.5) * SCALE_GAME));
      irr::scene::ISceneNodeAnimator	*anim;
      if (!(anim = Displayer::getSmgr()->createRotationAnimator(irr::core::vector3df(0.1f, 1.0f, 0.1f))))
      	return ;
      item->addAnimator(anim);
      anim->drop();
      irr::core::vector3df		extent = item->getTransformedBoundingBox().getExtent();
      irr::f32				factor = SCALE_GAME / 2 / extent.X;
      irr::core::vector3d<irr::f32>	factorEscalate(factor, factor, factor);
      item->setScale(factorEscalate);
      item->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
      _map[y][x]->setPowerup(item);
      delete tmp;
      addItem(x, y, static_cast<Items>(randVal));
    }
  else
    addItem(x, y, EMPTY);
}

void				Map::print() const
{
  for (unsigned int y = 0; y != _map.size(); y++)
    {
      for (unsigned int x = 0; x != _map[y].size(); x++)
	std::cout << static_cast<char>(_map[y][x]->getItem()) << std::flush;
      std::cout << std::endl;
    }
}

bool				Map::isAnObstacle(int const x, int const y, Players &players)
{
  if (x >= _maxX || y >= _maxY)
    return (true);
  char				item = _map[y][x]->getItem();
  if (item == BORDER
      || item == BREAKABLE_WALL
      || item == UNBREAKABLE_WALL
      || item == BOMB
      || item == FIRE)
    return (true);
  return (false);
}

void				Map::deletePowerup(int x, int y)
{
  if (y < 0 || x < 0 || x >= getMaxX() || y >= getMaxY())
    return ;
  Displayer::getSmgrMutex().lock();
  if (_map[y][x]->get3d())
    {
      _map[y][x]->get3d()->remove();
      _map[y][x]->setPowerup(NULL);
    }
  Displayer::getSmgrMutex().unlock();
}

void				Map::compareBonusAndPlayerPos(Player &player)
{
  FactoryPowerUps		factory;
  PowerUp			*tmp;

  if (player.getPosY() < 0 || player.getPosX() < 0 || player.getPosX() >= getMaxX() || player.getPosY() >= getMaxY())
    return ;
  if (player.getAlive() == true
      && _map[floor(player.getPosY())][floor(player.getPosX())]->getItem() >= 'a'
      && _map[floor(player.getPosY())][floor(player.getPosX())]->getItem() <= 'f')
    {
      if ((tmp = factory.createPowerUp(floor(player.getPosX()), floor(player.getPosY()), static_cast<Items>(_map[floor(player.getPosY())][floor(player.getPosX())]->getItem()))) != NULL)
	{
	  SDL::get().playSound(PICKPOWERUP);
	  tmp->PickedUp(&player);
	  addItem(player.getPosX(), floor(player.getPosY()), EMPTY);
	  delete tmp;
	}
      deletePowerup(floor(player.getPosX()), floor(player.getPosY()));
    }
}

void				Map::removeDanger(int const x, int const y,
						  int const finalRange)
{
  if (x >= _maxX || x < 0 || y >= _maxY || y < 0)
    return ;
  for (int i = x; i > 0 && i > x - finalRange; i--)
    if (_dangerMap[y][i]->getItem() == DANGEROUS
	&& _dangerMap[y][i]->getFirePower() > 0)
      {
	_dangerMap[y][i]->setFirePower(_dangerMap[y][i]->getFirePower() - 1);
	if (_dangerMap[y][i]->getFirePower() == 0
	    && _dangerMap[i][i]->getItem() != BORDER
	    && _dangerMap[y][i]->getItem() != UNBREAKABLE_WALL)
	  _dangerMap[y][i]->setItem(EMPTY);
      }
  for (int i = x; i < _maxX && i < x + finalRange; i++)
    if (_dangerMap[y][i]->getItem() == DANGEROUS
	&& _dangerMap[y][i]->getFirePower() > 0)
      {
	_dangerMap[y][i]->setFirePower(_dangerMap[y][i]->getFirePower() - 1);
	if (_dangerMap[y][i]->getFirePower() == 0
	    && _dangerMap[y][i]->getItem() != BORDER
	    && _dangerMap[y][i]->getItem() != UNBREAKABLE_WALL)
	  _dangerMap[y][i]->setItem(EMPTY);
      }

  for (int i = y; i > 0 && i > y - finalRange; i--)
    if (_dangerMap[i][x]->getItem() == DANGEROUS
	&& _dangerMap[i][x]->getFirePower() > 0)
      {
	_dangerMap[i][x]->setFirePower(_dangerMap[i][x]->getFirePower() - 1);
	if (_dangerMap[i][x]->getFirePower() == 0
	    && _dangerMap[i][x]->getItem() != BORDER
	    && _dangerMap[i][x]->getItem() != UNBREAKABLE_WALL)
	  _dangerMap[i][x]->setItem(EMPTY);
      }
  for (int i = y; i < _maxY && i < y + finalRange; i++)
    if (_dangerMap[i][x]->getItem() == DANGEROUS
	&& _dangerMap[i][x]->getFirePower() > 0)
      {
	_dangerMap[i][x]->setFirePower(_dangerMap[i][x]->getFirePower() - 1);
	if (_dangerMap[i][x]->getFirePower() == 0
	    && _dangerMap[i][x]->getItem() != BORDER
	    && _dangerMap[i][x]->getItem() != UNBREAKABLE_WALL)
	  _dangerMap[i][x]->setItem(EMPTY);
      }
}

void				Map::putDanger(int const x, int const y,
					       int const finalRange)
{
  int				pass = 0;

  if (x >= _maxX || x <= 0 || y >= _maxY || y <= 0)
    return ;
  for (int i = x; i > 0 && i > x - finalRange; i--)
    {
      if (_dangerMap[y][i]->getItem() == BORDER
	  || _dangerMap[y][i]->getItem() == UNBREAKABLE_WALL)
	break;
      if (_dangerMap[y][i]->getItem() == EMPTY
	  || _dangerMap[y][i]->getItem() == BONUS
	  || _dangerMap[y][i]->getItem() == BOMB
	  || _dangerMap[y][i]->getItem() == DANGEROUS
	  || _dangerMap[y][i]->getItem() == BREAKABLE_WALL)
	{
	  if (_dangerMap[y][i]->getItem() == BREAKABLE_WALL)
	    pass = 1;
	  _dangerMap[y][i]->setItem(DANGEROUS);
	  _dangerMap[y][i]->setFirePower(_dangerMap[y][i]->getFirePower() + 1);
	  if (pass == 1)
	    break;
	}
    }
  for (int i = x; i < _maxX && i < x + finalRange; i++)
    {
      pass = 0;
      if (_dangerMap[y][i]->getItem() == BORDER
	  || _dangerMap[y][i]->getItem() == UNBREAKABLE_WALL)
	break;
      if (_dangerMap[y][i]->getItem() == EMPTY
	  || _dangerMap[y][i]->getItem() == BONUS
	  || _dangerMap[y][i]->getItem() == BOMB
	  || _dangerMap[y][i]->getItem() == DANGEROUS
	  || _dangerMap[y][i]->getItem() == BREAKABLE_WALL)
	{
	  if (_dangerMap[y][i]->getItem() == BREAKABLE_WALL)
	    pass = 1;
	  _dangerMap[y][i]->setItem(DANGEROUS);
	  _dangerMap[y][i]->setFirePower(_dangerMap[y][i]->getFirePower() + 1);
	  if (pass == 1)
	    break;
	}
    }

  for (int i = y; i > 0 && i > y - finalRange; i--)
    {
      pass = 0;
      if (_dangerMap[i][x]->getItem() == BORDER
	  || _dangerMap[i][x]->getItem() == UNBREAKABLE_WALL)
	break;
      if (_dangerMap[i][x]->getItem() == EMPTY
	  || _dangerMap[i][x]->getItem() == BONUS
	  || _dangerMap[i][x]->getItem() == BOMB
	  || _dangerMap[i][x]->getItem() == DANGEROUS
	  || _dangerMap[i][x]->getItem() == BREAKABLE_WALL)
	{
	  if (_dangerMap[i][x]->getItem() == BREAKABLE_WALL)
	    pass = 1;
	  _dangerMap[i][x]->setItem(DANGEROUS);
	  _dangerMap[i][x]->setFirePower(_dangerMap[i][x]->getFirePower() + 1);
	  if (pass == 1)
	    break;
	}
    }
  for (int i = y; i < _maxY && i < y + finalRange; i++)
    {
      pass = 0;
      if (_dangerMap[i][x]->getItem() == BORDER
	  || _dangerMap[i][x]->getItem() == UNBREAKABLE_WALL)
	break;
      if (_dangerMap[i][x]->getItem() == EMPTY
	  || _dangerMap[i][x]->getItem() == BONUS
	  || _dangerMap[i][x]->getItem() == BOMB
	  || _dangerMap[i][x]->getItem() == DANGEROUS
	  || _dangerMap[i][x]->getItem() == BREAKABLE_WALL)
	{
	  if (_dangerMap[i][x]->getItem() == BREAKABLE_WALL)
	    pass = 1;
	  _dangerMap[i][x]->setItem(DANGEROUS);
	  _dangerMap[i][x]->setFirePower(_dangerMap[i][x]->getFirePower() + 1);
	  if (pass == 1)
	    break;
	}
    }
}
