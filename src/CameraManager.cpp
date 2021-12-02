//
// CameraManager.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed Apr 27 15:23:20 2016 guillaume wilmot
// Last update Sun Jun  5 15:03:02 2016 guillaume wilmot
//

#include "StaticCamera.hpp"
#include "FpsCamera.hpp"
#include "CameraManager.hpp"

CameraManager::CameraManager(irr::scene::ISceneManager *smgr, EventHandler *receiver)
{
  _smgr = smgr;
  if (!(_staticCamera = new StaticCamera(smgr, this, receiver)) ||
      !(_fpsCamera = new FpsCamera(smgr, this, receiver)))
    throw std::exception(); //"Could not allocate Camera"
  _smgr->setActiveCamera(_staticCamera->getCam());
  _current = false;
  _currentCamera = _staticCamera;
}

CameraManager::~CameraManager() {}

void				CameraManager::switchCamera(irr::scene::IAnimatedMeshSceneNode *player)
{
  if (_current)
    _currentCamera = _staticCamera;
  else
    _currentCamera = _fpsCamera;
  _smgr->setActiveCamera(_currentCamera->getCam());
  _current = !_current;
}

void				CameraManager::setPlayer(std::vector<Player *> const &player) const
{
  _fpsCamera->setPlayer(player);
  _staticCamera->setPlayer(player);
}

bool				CameraManager::getCurrent() const
{
  return (_current);
}

ICamera				*CameraManager::getCamera() const
{
  return (_currentCamera);
}
