//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:10:09 2016 Alban Combaud
//

# include "DisplayNewGame.hh"
# include "Back.hh"
# include "Play.hh"
# include "gui.hh"

Play::Play()
{
}

Play::~Play()
{
}

std::string	Play::getName() const
{
  return std::string("Play");
}

int	Play::getType() const
{
  return 0;
}

void		Play::launch()
{
  Menu					*menu = Menu::getMenu(NULL);
  Gui					*gui = Gui::getGui(NULL);
  std::vector<IModule *>		tmp;

   gui->init();
  tmp.push_back(new DisplayNewGame);
  tmp.push_back(new Back(menu->getMods()));
  menu->changeMods(tmp);
  gui->add_buttons(menu->getMods(), 0.2);
}
