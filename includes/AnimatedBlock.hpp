//
// AnimatedBlock.hpp for  in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 15 02:45:41 2016 guillaume wilmot
// Last update Sun Jun  5 17:39:40 2016 guillaume wilmot
//

#ifndef ANIMATEDBLOCK_HPP_
# define ANIMATEDBLOCK_HPP_

# include <iostream>
# include <string>
# include <map>
# include "irrlicht.h"
# include "IAnimatedBlock.hpp"

class		AnimatedBlock : public IAnimatedBlock {
public:
  AnimatedBlock(irr::scene::IAnimatedMeshSceneNode *block) {_block = block;}
  virtual			~AnimatedBlock() {}

  void					playAnim(const std::string &idx)
  {
    if (_anims[idx] && idx != _act)
      {
	_block->setFrameLoop(_anims[idx][0], _anims[idx][1]);
	_act = idx;
      }
    if (!_anims[idx])
      std::cerr << "No such animation" << std::endl;
  }
  irr::scene::IAnimatedMeshSceneNode	*getBlock() {return (_block);}

protected:
  irr::scene::IAnimatedMeshSceneNode	*_block;
  std::map<std::string, int *>		_anims;
  std::string				_act;
};

#endif /* !ANIMATEDBLOCK_HPP_ */
