//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:07:39 2016 Alban Combaud
//

# include "Back.hh"
# include "HighScores.hh"
# include "gui.hh"
# include "DisplayHighscores.hh"
# include "Sdl.hpp"

HighScores::HighScores()
{
}

HighScores::~HighScores()
{
}

int	HighScores::getType() const
{
  return 0;
}

std::string	HighScores::getName() const
{
  return "HighScores";
}

void		HighScores::launch()
{
  Menu					*menu = Menu::getMenu(NULL);
  Gui					*gui = Gui::getGui(NULL);
  std::vector<IModule *>		tmp;

  Mix_PauseMusic();
  SDL::get().playSound(HIGHSCORES_MUSIC);
  gui->init();
  tmp.push_back(new DisplayHighScores);
  tmp.push_back(new Back(menu->getMods()));
  menu->changeMods(tmp);
  gui->add_buttons(menu->getMods(), 0.2);
}
