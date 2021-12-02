//
// Options.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:12:59 2016 Alban Combaud
//

#ifndef OPTIONS_HH_
# define OPTIONS_HH_

# include "IModule.hpp"
# include "Menu.hh"

class Options : public IModule
{
public:
  Options();
  ~Options();

  int                           getType() const;
  std::string			getName() const;
  void				launch();
};

#endif
