//
// Steve.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 15 03:27:10 2016 guillaume wilmot
// Last update Sat Jun  4 02:02:34 2016 guillaume wilmot
//

#ifndef STEVE_HPP_
# define STEVE_HPP_

# include "AnimatedBlock.hpp"

class		Steve : public AnimatedBlock {
public:
  Steve(irr::scene::IAnimatedMeshSceneNode *block) : AnimatedBlock(block)
  {
    _block = block;
    _anims["idle"] = new int[2]; _anims["idle"][0] = 0; _anims["idle"][1] = 80;
    _anims["walk"] = new int[2]; _anims["walk"][0] = 168; _anims["walk"][1] = 188;
    _anims["hit"] = new int[2]; _anims["hit"][0] = 189; _anims["hit"][1] = 199;
    _anims["walkHit"] = new int[2]; _anims["walkHit"][0] = 200; _anims["walkHit"][1] = 220;
    _anims["putBomb"] = new int [2]; _anims["putBomb"][0] = 221; _anims["putBomb"][1] = 232;
    _anims["die"] = new int[2]; _anims["die"][0] = 233; _anims["die"][1] = 251;
    _block->setAnimationSpeed(15);
    _block->setLoopMode(true);
    playAnim("idle");
  }
  ~Steve()
  {
    delete _anims["idle"];
    delete _anims["walk"];
    delete _anims["hit"];
    delete _anims["walkHit"];
    delete _anims["putBomb"];
    delete _anims["die"];
  }
};

#endif /* !STEVE_HPP_ */
