//
// Fire.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 15 03:27:10 2016 guillaume wilmot
// Last update Tue May 24 16:31:50 2016 guillaume wilmot
//

#ifndef FIRE_HPP_
# define FIRE_HPP_

# include "AnimatedBlock.hpp"

class		Fire : public AnimatedBlock {
public:
  Fire(irr::scene::IAnimatedMeshSceneNode *block) : AnimatedBlock(block)
  {
    _block = block;
    _anims["idle"] = new int[2]; _anims["idle"][0] = 0; _anims["idle"][1] = 250;
    _block->setAnimationSpeed(20);
    _block->setLoopMode(true);
    playAnim("idle");
  }
  ~Fire() {delete _anims["idle"];}
};

#endif /* !FIRE_HPP_ */
