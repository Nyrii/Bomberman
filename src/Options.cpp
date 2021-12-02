//
// Options.cpp for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:36:49 2016 Alban Combaud
//

# include "Sound.hh"
# include "Binding.hh"
# include "Back.hh"
# include "Options.hh"
# include "gui.hh"
# include <unistd.h>

Options::Options()
{
}

Options::~Options()
{
}

int	Options::getType() const
{
  return 0;
}

std::string	Options::getName() const
{
  return "Options";
}

void		Options::launch()
{
  Menu					*menu = Menu::getMenu(NULL);
  Gui					*gui = Gui::getGui(NULL);
  std::vector<IModule *>		tmp;

  gui->init();
  tmp.push_back(new Sound);
  tmp.push_back(new Binding);
  tmp.push_back(new Back(menu->getMods()));
  menu->changeMods(tmp);
  gui->add_buttons(menu->getMods(), 0.2);
}
