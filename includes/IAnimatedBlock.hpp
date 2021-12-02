//
// IAnimatedBlock.hpp for  in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 15 02:45:41 2016 guillaume wilmot
// Last update Tue May 24 16:18:19 2016 guillaume wilmot
//

#ifndef IANIMATEDBLOCK_HPP_
# define IANIMATEDBLOCK_HPP_

# include <string>
# include "irrlicht.h"

class		IAnimatedBlock {
public:
  virtual			~IAnimatedBlock() {}

  virtual void					playAnim(const std::string &) = 0;
  virtual irr::scene::IAnimatedMeshSceneNode	*getBlock() = 0;
};

#endif /* !IANIMATEDBLOCK_HPP_ */
