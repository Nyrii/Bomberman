//
// Main.cpp for Main in /Users/noboud_n/Documents/Share/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Wed Jun  1 16:48:10 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 19:05:04 2016 Alban Combaud
//

# include "gui.hh"
# include "Menu.hh"
# include "Sdl.hpp"
# include "Error.hpp"
# include "Game.hpp"

int		main()
{
  SDL::get().init();
  Gui		gui;
  Menu		menu;
  NoLogger	nL;
      
  gui.playVideo("./ressources/videos/ScredSplashScreen.mp4", MUSIC_SPLASH, false);
  Mix_HaltChannel(-1);
  gui.playVideo("./ressources/videos/ScredIntro.mp4", MUSIC_INTRO, true);
  Mix_HaltChannel(-1);
  SDL::get().playMusic(MENU_THEME);
  Menu::getMenu(&menu);
  Gui::getGui(&gui);
  while (1)
    {
      try {
	menu.init();
	gui.init();
	gui.add_buttons(menu.getMods(), 0.1);
	while (gui.getDevice()->run())
	  {
	    gui.getDriver()->beginScene(true, true, irr::video::SColor(100, 0, 0, 0));
	    gui.getSceneManager()->drawAll();
	    gui.display();
	    gui.getDriver()->endScene();
	  }
      } catch (const std::exception &e)
	{
	  std::cout << e.what() << std::endl;
	  return (-1);
	}
      gui.destroy();
      gui.getDevice()->drop();
    }
  return (0);
}
