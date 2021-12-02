//
// Back.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 05:24:21 2016 Alban Combaud
//

#ifndef BACK_HH_
# define BACK_HH_

# include "IModule.hpp"
# include "Menu.hh"
# include "gui.hh"

class Pause
{
private:
public:
  Pause();
  ~Pause();

  void			       init_buttons();
  bool			       OnContinue(const CEGUI::EventArgs &);
  bool			       OnLeave(const CEGUI::EventArgs &);
};

#endif
