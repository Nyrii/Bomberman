//
// DisplaySound.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:16:15 2016 Alban Combaud
//

#ifndef DISPLAYSOUND_HH_
# define DISPLAYSOUND_HH_

# include "IModule.hpp"
# include "Menu.hh"

class DisplaySound : public IModule
{
public:
  DisplaySound();
  ~DisplaySound();

  std::string			getName() const;
  int                           getType() const;
  void				launch();
};

#endif

