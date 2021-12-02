//
// FpsCamera.hh for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Fri Apr 29 13:54:22 2016 guillaume wilmot
// Last update Sun Jun  5 16:06:48 2016 guillaume wilmot
//

#ifndef FPSCAMERA_HH_
# define FPSCAMERA_HH_

# include "Camera.hpp"
# include "CameraManager.hpp"

class CameraManager;

class		FpsCamera : public Camera {
public:
  FpsCamera(irr::scene::ISceneManager *, CameraManager * const, EventHandler *);
  ~FpsCamera() {}

  void			setPlayer(std::vector<Player *> const &);
  void                  putCam(irr::core::vector3df &);
};

#endif /* !FPSCAMERA_HH_ */
