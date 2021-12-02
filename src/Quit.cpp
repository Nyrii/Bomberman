//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:10:19 2016 Alban Combaud
//

# include "Quit.hh"
# include "gui.hh"

Quit::Quit()
{
}

Quit::~Quit()
{
}

int	Quit::getType() const
{
  return 0;
}

std::string	Quit::getName() const
{
  return std::string("Quit");
}

void		Quit::launch()
{
  Gui		*gui = Gui::getGui(NULL);

  gui->destroy();
  exit(0);
}
