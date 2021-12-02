//
// DisplayBinding.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:17:18 2016 Alban Combaud
//

#ifndef DISPLAYCREDITS_HH_
# define DISPLAYCREDITS_HH_

# include "IModule.hpp"
# include "Menu.hh"

class DisplayCredits : public IModule
{
public:
  DisplayCredits();
  ~DisplayCredits();

  std::string			getName() const;
  int                           getType() const;
  void				launch();
};

#endif

