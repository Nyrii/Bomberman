//
// ICamera.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Fri Apr 29 13:32:07 2016 guillaume wilmot
// Last update Fri Jun  3 23:30:07 2016 Nyrandone Noboud-Inpeng
//

#ifndef ICAMERA_HPP_
# define ICAMERA_HPP_

# include <vector>
# include <irrlicht.h>
# include "Player.hpp"

class			ICamera {
public:
  virtual				~ICamera() {}

  virtual irr::scene::ICameraSceneNode	*getCam() const = 0;
  virtual int				manageEvents(const float, Map &) = 0;
  virtual void				setPlayer(std::vector<Player *> const &) = 0;
};

#endif /* !ICAMERA_HPP_ */
