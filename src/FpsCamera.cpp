//
// FpsCamera.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Fri Apr 29 20:10:58 2016 guillaume wilmot
// Last update Sun Jun  5 21:53:43 2016 guillaume wilmot
//

#include <stdexcept>
#include <iostream>
#include "FpsCamera.hpp"
#include "Displayer.hpp"

FpsCamera::FpsCamera(irr::scene::ISceneManager *, CameraManager * const manager, EventHandler *e)
{
  if (!(_camera = Displayer::getSmgr()->addCameraSceneNode(0, irr::core::vector3df(0, 50, 0), irr::core::vector3df(0, 0, 0), -1, false)))
    throw std::exception();
  _manager = manager;
  _receiver = e;
}

void				FpsCamera::setPlayer(std::vector<Player *> const &players)
{
  _player = players;
}

void				FpsCamera::putCam(irr::core::vector3df &playerPosition)
{
  Direction			dir = _player[0]->getCurDirection();

  _camera->setTarget(playerPosition);
  playerPosition.Y = _player[0]->getSteve()->getBlock()->getTransformedBoundingBox().getExtent().Y + 20;
  _camera->setPosition(playerPosition);
}
