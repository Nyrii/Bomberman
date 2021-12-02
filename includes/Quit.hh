//
// Quit.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:12:40 2016 Alban Combaud
//

#ifndef QUIT_HH_
# define QUIT_HH_

# include "IModule.hpp"
# include "Menu.hh"

class Quit : public IModule
{
public:
  Quit();
  ~Quit();

  std::string			getName() const;
  int                           getType() const;
  void				launch();
};

#endif
