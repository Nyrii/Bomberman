//
// StaticCamera.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Fri Apr 29 20:08:00 2016 guillaume wilmot
// Last update Sun Jun  5 22:02:17 2016 guillaume wilmot
//

#include <stdexcept>
#include "StaticCamera.hpp"
#include "EventHandler.hpp"

StaticCamera::StaticCamera(irr::scene::ISceneManager *smgr, CameraManager * const manager, EventHandler *e)
{
  if (!(_camera = smgr->addCameraSceneNode(0, irr::core::vector3df(0, 50, 0), irr::core::vector3df(0, 0, 0))))
    throw std::exception();

  _camera->setRotation(irr::core::vector3df(0, 0, 180));
  _manager = manager;
  _receiver = e;
}

void		StaticCamera::putCam(irr::core::vector3df &) {}
