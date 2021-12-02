//
// gui.hh for  in /home/combau_a/rendu/test/save/irlich/newtest
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Sun May  1 11:32:28 2016 Alban Combaud
// Last update Sun Jun  5 21:29:29 2016 Alban Combaud
//

#ifndef GUI_HH_
# define GUI_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_mixer.h>
# include <iostream>
# include <CEGUI.h>
# include <RendererModules/Irrlicht/Renderer.h>
# include <irrlicht.h>

# include "opencv2/opencv.hpp"
# include "opencv2/highgui/highgui.hpp"
# include "Mutex.hpp"
# include "IModule.hpp"
# include "Enum.hh"

class Gui : public irr::IEventReceiver
{
public:
  Gui();
  ~Gui();

  //// METHODS
  void		init(int = 1920, int = 1080);
  void		destroy();
  void		display();
  void		loadFonts(const std::string &);
  void		loadSchemes(const std::string &);
  CEGUI::Window	*createWindow(const std::string &scheme, const std::string &name,
			      float xPer, float yPer, float xPerSize, float yPerSize);
  void		setMouseSkin(const std::string &);
  void		showMouse(const bool &);
  bool		OnEvent(const irr::SEvent &e);
  void		add_buttons(const std::vector<IModule *> &, float);
  void		playVideo(const std::string &, e_sound, bool);

  ///// GETTERS
  irr::IrrlichtDevice		*getDevice() const;
  irr::video::IVideoDriver	*getDriver() const;
  irr::scene::ISceneManager	*getSceneManager() const;
  CEGUI::IrrlichtRenderer	*getRend() const;
  CEGUI::GUIContext		*getContext() const;
  irr::EKEY_CODE		getPress() const;
  void				setPress(const irr::EKEY_CODE &);
  CEGUI::Window			*getWin() const;

  static Gui			*getGui(Gui *tmp)
  {
    static Gui		*_gui = NULL;

    if (_gui == NULL || tmp != NULL)
      _gui = tmp;
    return _gui;
  };

private:
  ///// IRRLICHT
  irr::IrrlichtDevice		*_device;
  irr::video::IVideoDriver	*_driver;
  irr::scene::ISceneManager	*_sceneManager;
  irr::EKEY_CODE		_press;

  //// CEGUI
  CEGUI::IrrlichtRenderer	*_rend;
  CEGUI::GUIContext		*_context;
  CEGUI::Window			*_win;
};

class NoLogger : public CEGUI::Logger
{
  void logEvent (const CEGUI::String&, CEGUI::LoggingLevel) {}
  void setLogFilename(const CEGUI::String&, bool) {}
};

#endif
