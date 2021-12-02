//
// CameraManager.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed Apr 27 15:08:37 2016 guillaume wilmot
// Last update Fri Jun  3 12:21:44 2016 Nyrandone Noboud-Inpeng
//

#ifndef CAMERAMANAGER_HPP_
# define CAMERAMANAGER_HPP_

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

# include "irrlicht.h"
# include "ICamera.hpp"
# include "EventHandler.hpp"

class			CameraManager {
public:
  CameraManager(irr::scene::ISceneManager *, EventHandler *);
  ~CameraManager();

  void				switchCamera(irr::scene::IAnimatedMeshSceneNode * = NULL);
  void				setPlayer(std::vector<Player *> const &) const;
  bool				getCurrent() const;
  ICamera			*getCamera() const;

private:

  irr::scene::ISceneManager	*_smgr;
  ICamera			*_staticCamera;
  ICamera			*_fpsCamera;
  ICamera			*_currentCamera;
  bool				_current;
};

#endif /* CAMERAMANAGER_HPP_ */
