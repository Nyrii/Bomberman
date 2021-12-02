//
// Camera.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Fri Apr 29 13:32:07 2016 guillaume wilmot
// Last update Sun Jun  5 14:33:40 2016 guillaume wilmot
//

#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include <vector>
# include "Map.hh"
# include "irrlicht.h"
# include "ICamera.hpp"
# include "CameraManager.hpp"
# include "EventHandler.hpp"

class CameraManager;

class			Camera : public ICamera {
public:
  virtual				~Camera() {_camera = NULL;}

  int					manageEvents(const float, Map &);
  irr::scene::ICameraSceneNode		*getCam() const {return (_camera);}
  virtual void				setPlayer(std::vector<Player *> const &player) = 0;
  virtual void				putCam(irr::core::vector3df &) = 0;
protected:
  irr::scene::ICameraSceneNode		*_camera;
  std::vector<Player *>			_player;
  CameraManager				*_manager;
  EventHandler				*_receiver;
};

#endif /* !CAMERA_HPP_ */
