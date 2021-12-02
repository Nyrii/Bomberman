//
// Back.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:16:43 2016 Alban Combaud
//

#ifndef BACK_HH_
# define BACK_HH_

# include "IModule.hpp"
# include "Menu.hh"
# include "gui.hh"

class Back : public IModule
{
private:
  std::vector<IModule *>		_lastMenu;
  CEGUI::Slider				*_slider;
public:
  Back(const std::vector<IModule *> &);
  ~Back();

  std::string			getName() const;
  int                           getType() const;
  int				getNb() const;
  void				setSlider(CEGUI::Slider *);
  void				launch();
};

#endif
