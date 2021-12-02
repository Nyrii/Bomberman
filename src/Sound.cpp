//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:05:44 2016 Alban Combaud
//

# include "Back.hh"
# include "Sound.hh"
# include "DisplaySound.hh"
# include "gui.hh"

Sound::Sound() : _volume(100.0)
{
}

Sound::~Sound()
{
}

int	Sound::getType() const
{
  return 0;
}

std::string	Sound::getName() const
{
  return std::string("Sound");
}

float		Sound::getVolume() const
{
  return _volume;
}

void		Sound::setVolume(const float &vol)
{
  _volume = vol;
}

void	Sound::launch()
{
  Menu					*menu = Menu::getMenu(NULL);
  Gui					*gui = Gui::getGui(NULL);
  std::vector<IModule *>		tmp;

  gui->init();
  tmp.push_back(new DisplaySound);
  tmp.push_back(new Back(menu->getMods()));
  menu->changeMods(tmp);
  gui->add_buttons(menu->getMods(), 0.2);
}
