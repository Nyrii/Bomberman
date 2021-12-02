//
// FireManager.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 15 21:35:16 2016 guillaume wilmot
// Last update Sun Jun  5 21:49:20 2016 guillaume wilmot
//

#ifndef FIREMANAGER_HPP_
# define FIREMANAGER_HPP_

# include <vector>
# include <iostream>
# include <iostream>
# include "irrlicht.h"
# include "Fire.hpp"
# include "Tile.hh"

class		FireManager {
public:
  FireManager() {}
  ~FireManager() {}

  int			init(const std::vector<std::vector<Tile *>> &);
  void			putFire(int, int);
  void			removeFire(int, int);
  int			clean();

private:
  Fire			*newFire(int, int, irr::scene::ISceneManager *) const;

  irr::core::array<irr::video::ITexture *>	_textureArray;
  irr::scene::ISceneNodeAnimator		*_textureAnimator;
  irr::scene::IAnimatedMesh			*_mesh;
  std::vector<std::vector<Fire *> *>		_fire;
};

#endif /* FIREMANAGER_HPP_ */
