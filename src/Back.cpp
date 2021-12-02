//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:36:34 2016 Alban Combaud
//

# include "Online.hh"
# include "Back.hh"
# include "gui.hh"
# include "Sdl.hpp"
# include "DisplayNewGame.hh"

Back::Back(const std::vector<IModule *> &last) : _lastMenu(last), _slider(NULL)
{
}

Back::~Back()
{
}

void				Back::setSlider(CEGUI::Slider *tmp)
{
  _slider = tmp;
}

int	Back::getType() const
{
  return 0;
}

std::string	Back::getName() const
{
  return std::string("Back");
}

void		Back::launch()
{
  Menu					*menu = Menu::getMenu(NULL);
  Gui					*gui = Gui::getGui(NULL);

  if (menu->getMods()[0]->getType() == 2)
    static_cast<DisplayNewGame *>(menu->getMods()[0])->deletePlayers();
  Mix_HaltChannel(-1);
  SDL::get().actualizeVolume(MENU_THEME);
  Mix_ResumeMusic();
  if (_slider != NULL)
    {
      menu->setSound(_slider->getCurrentValue());
      SDL::get().setVolume(menu->getSound());
      SDL::get().actualizeVolume(MENU_THEME);
      Mix_ResumeMusic();
    }
  gui->init();
  menu->changeMods(_lastMenu);
  gui->add_buttons(menu->getMods(), 0.2);
}
