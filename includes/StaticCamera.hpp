//
// StaticCamera.hh for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Fri Apr 29 13:54:22 2016 guillaume wilmot
// Last update Sun Jun  5 14:30:27 2016 guillaume wilmot
//

#ifndef STATICCAMERA_HH_
# define STATICCAMERA_HH_

# include "Map.hh"
# include "CameraManager.hpp"
# include "Camera.hpp"

class CameraManager;

class		StaticCamera : public Camera {
public:
  StaticCamera(irr::scene::ISceneManager *smgr, CameraManager * const, EventHandler *);
  ~StaticCamera() {}

  void			setPlayer(std::vector<Player *> const &player) {_player = player;}
  void			putCam(irr::core::vector3df &);
};

#endif /* !STATICCAMERA_HH_ */
