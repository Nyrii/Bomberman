//
// Tile.cpp for Tile in /Users/noboud_n/Documents/Share/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue May 24 15:04:25 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 03:03:35 2016 Nyrandone Noboud-Inpeng
//

#include "Displayer.hpp"
#include "Tile.hh"
#include "MeshError.hpp"
#include "Sdl.hpp"

Tile::Tile(char const &item, const float y, const float x)
{
  _suddened = false;
  _powerup._var = NULL;
  _wall._var = NULL;
  _ground._var = NULL;
  _item._var = item;
  _posY._var = y;
  _posX._var = x;
  _firePower._var = 0;
}

Tile::~Tile() {}

int				Tile::init(irr::scene::ISceneManager *smgr)
{
  irr::scene::IMesh		*stone = NULL;
  irr::scene::IMesh		*wall = NULL;

  if (_suddened)
    return (0);
  if (_item.get() == BORDER || _item.get() == UNBREAKABLE_WALL)
    {
      if (!(wall = smgr->getMesh("./assets/Blocks/StoneBrickPillar.obj")))
	return (std::cerr << "Can't init tile" << std::endl, -1);
    }
  else if (_item.get() == BREAKABLE_WALL)
    {
      if (!(wall = smgr->getMesh("./assets/Blocks/Planks.obj")))
	return (std::cerr << "Can't init tile" << std::endl, -1);
    }
  if (!(stone = smgr->getMesh("./assets/Blocks/Stone.obj")))
    return (std::cerr << "Can't init tile" << std::endl, -1);

  _ground._var = new Block(_posX.get(), -1, _posY.get(), stone, smgr);
  wall ? _wall._var = new Block(_posX.get(), 0, _posY.get(), wall, smgr) : 0;

  if ((wall && _wall.get()->create(SCALE_GAME) == -1) || _ground.get()->create(SCALE_GAME) == -1)
    return (std::cerr << "Can't init tile" << std::endl, -1);
  return (0);
}

void				Tile::destroy()
{
  ScopedLock			lock1(Displayer::getSmgrMutex());
  ScopedLock			lock(_wall._mutex);

  if (_wall._var)
    _wall._var->destroy();
  _wall._var = NULL;
}

float				Tile::getPosX()
{
  return (_posX.get());
}

float				Tile::getPosY()
{
  return (_posY.get());
}

char				Tile::getItem()
{
  return (_item.get());
}

int				Tile::getFirePower()
{
  return (_firePower.get());
}

Block				*Tile::getGround()
{
  return (_ground.get());
}

Block				*Tile::getWall()
{
  return (_wall.get());
}

irr::scene::IMeshSceneNode	*Tile::get3d()
{
  return (_powerup.get());
}

void				Tile::setPowerup(irr::scene::IMeshSceneNode *s)
{
  _powerup.set(s);
}

void				Tile::setPosX(const float x)
{
  _posX.set(x);
}

void				Tile::setPosY(const float y)
{
  _posY.set(y);
}

void				Tile::setItem(const char &item)
{
  _item.set(item);
  if (!_suddened && item == BORDER)
    {
      SDL::get().playSound(FALLINGBLOCK);
      init(Displayer::getSmgr());
      _suddened = true;
    }
}

void				Tile::setFirePower(const int &firePower)
{
  _firePower.set(firePower);
}
