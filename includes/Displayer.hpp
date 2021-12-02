//
// Displayer.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed Apr 27 10:41:04 2016 guillaume wilmot
// Last update Sun Jun  5 21:46:38 2016 guillaume wilmot
//

#ifndef DISPLAYER_HPP_
# define DISPLAYER_HPP_

#ifdef _IRR_WINDOWS_
# pragma comment(lib, "Irrlicht.lib")
# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

# include "irrlicht.h"
# include "EventHandler.hpp"
# include "CameraManager.hpp"
# include "Axes.hpp"
# include "Game.hpp"
# include "Block.hpp"
# include "Scale.hh"
# include "AnimatedBlock.hpp"

class		Displayer {
public:
  Displayer();
  ~Displayer();

  void					setCaption(const irr::core::stringw &caption);
  int					display(Game &, ProtectedVar<bool> *, ProtectedVar<bool> *);

  static irr::scene::ISceneManager	*getSmgr(irr::scene::ISceneManager *smgr = NULL)
  {
    static irr::scene::ISceneManager	*_smgr = NULL;
    _smgr = smgr ? smgr : _smgr;
    return (_smgr);
  }
  static Mutex				&getSmgrMutex()
  {
    static Mutex			mutex;

    return (mutex);
  }
  static irr::video::IVideoDriver	*getDriver(irr::video::IVideoDriver *driver = NULL)
  {
    static irr::video::IVideoDriver	*_driver = NULL;
    _driver = driver ? driver : _driver;
    return (_driver);
  }

private:

  static void			threadEvents(Players &, std::vector<Player *> &,
					     std::vector<Player *> &, Game &,
					     ProtectedVar<bool> *, Displayer * const);

  void				instanciateLight(Map &);
  void				renderMap(Map &);
  void				updateFPS();
  void				updatePlayers3d(Players &);
  void				updatePlayersObj(Players &);
  void				movePlayers(std::vector<Player *> const &, const irr::f32);
  int				manageEvents(Players &, std::vector<Player *> const &,
					     std::vector<Player *> const &, Map, ProtectedVar<bool> *);

  //Irrlicht
  EventHandler			_receiver;
  irr::IrrlichtDevice		*_device;
  irr::video::IVideoDriver	*_driver;
  irr::scene::ISceneManager	*_smgr;
  irr::gui::IGUIEnvironment	*_guienv;

  //Window
  irr::core::stringw		_caption;
  irr::u32			_then;
  int				_lastFPS;

  //Miscelanneous
  CameraManager			*_cameras;
  irr::scene::ISceneNode	*_skydome;

  /**/
  AxesSceneNode			*_axes;
  /**/
};

#endif /* DISPLAYER_HPP_ */
