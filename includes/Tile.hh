//
// Tile.hh for Tile in /Users/noboud_n/Documents/Share/cpp_indie_studio/includes/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue May 24 15:03:08 2016 Nyrandone Noboud-Inpeng
// Last update Sat Jun  4 21:38:32 2016 guillaume wilmot
//

#ifndef TILE_HH_
# define TILE_HH_

# include "irrlicht.h"
# include "Enum.hh"
# include "Block.hpp"
# include "ProtectedVar.hpp"

class				Tile
{
public:
  Tile(char const &, const float, const float);
  ~Tile();

  int				init(irr::scene::ISceneManager *);

  void				destroy();

  Block				*getGround();
  Block				*getWall();
  float				getPosX();
  float				getPosY();
  char				getItem();
  int				getFirePower();
  irr::scene::IMeshSceneNode	*get3d();

  void				createItem(int, int);
  void				setPowerup(irr::scene::IMeshSceneNode *);
  void				setPosX(const float);
  void				setPosY(const float);
  void				setItem(const char &);
  void				setFirePower(const int &);

private:

  ProtectedVar<irr::scene::IMeshSceneNode *>	_powerup;
  bool				_suddened;
  ProtectedVar<Block *>		_ground;
  ProtectedVar<Block *>		_wall;
  ProtectedVar<float>		_posX;
  ProtectedVar<float>		_posY;
  ProtectedVar<char>		_item;
  ProtectedVar<int>		_firePower;
};

#endif /* !TILE_HH_ */
