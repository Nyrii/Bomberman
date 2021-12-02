//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:10:36 2016 Alban Combaud
//

# include "Back.hh"
# include "Binding.hh"
# include "DisplayBinding.hh"
# include "gui.hh"

Binding::Binding()
{
}

Binding::~Binding()
{
}

int	Binding::getType() const
{
  return 0;
}

std::string	Binding::getName() const
{
  return std::string("Controls");
}

void		Binding::launch()
{
  Menu					*menu = Menu::getMenu(NULL);
  Gui					*gui = Gui::getGui(NULL);
  std::vector<IModule *>		tmp;

  gui->init();
  tmp.push_back(new DisplayBinding);
  tmp.push_back(new Back(menu->getMods()));
  menu->changeMods(tmp);
  gui->add_buttons(menu->getMods(), 0.2);
}
