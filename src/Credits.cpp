//
// Credits.cpp for  in /home/combau_a/rendu/cpp_indie_studio
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:42:40 2016 Aurelien Arino
//

# include <iostream>
# include <fstream>
# include "Back.hh"
# include "Credits.hh"
# include "DisplayCredits.hh"
# include "gui.hh"
# include "Sdl.hpp"

Credits::Credits()
{}

Credits::~Credits() {}

int	Credits::getType() const
{
  return 0;
}

std::string	Credits::getName() const
{
  return "Credits";
}

std::vector<std::string>	Credits::getCredits() const {
  return _credits;
}

void Credits::fetchCredits() {
  char c;
  std::ifstream fs(".credits");
  std::string	str;

  if (fs.good())
    while (std::getline(fs, str))
      _credits.push_back(str);
  else
    std::cerr << "Error : Cannot read or acces to credits file." << std::endl;
  fs.close();
}

void		Credits::launch()
{
  Menu					*menu = Menu::getMenu(NULL);
  Gui					*gui = Gui::getGui(NULL);
  std::vector<IModule *>		tmp;

  Mix_PauseMusic();
  SDL::get().playSound(CREDITS_MUSIC);
  gui->init();
  tmp.push_back(new DisplayCredits);
  tmp.push_back(new Back(menu->getMods()));
  menu->changeMods(tmp);
  gui->add_buttons(menu->getMods(), 0.2);
}
