//
// Bomb.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Tue May 31 20:27:30 2016 guillaume wilmot
// Last update Sat Jun  4 00:15:34 2016 guillaume wilmot
//

#ifndef BOMB3D_HPP_
# define BOMB3D_HPP_

# include "AnimatedBlock.hpp"

class		Bomb3d : public AnimatedBlock {
public:
  Bomb3d(irr::scene::IAnimatedMeshSceneNode *block) : AnimatedBlock(block)
  {
    _block = block;
    _anims["idle"] = new int[2]; _anims["idle"][0] = 0; _anims["idle"][1] = 0;
    _anims["explode"] = new int[2]; _anims["explode"][0] = 0; _anims["explode"][1] = 30;
    _block->setAnimationSpeed(15);
    _block->setLoopMode(true);
    playAnim("idle");
  }
  ~Bomb3d()
  {
    delete _anims["idle"];
    delete _anims["explode"];
  }
};

#endif /* !BOMB3D_HPP_ */
