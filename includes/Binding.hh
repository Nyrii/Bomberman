//
// Binding.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:16:51 2016 Alban Combaud
//

#ifndef BINDING_HH_
# define BINDING_HH_

# include "IModule.hpp"
# include "Menu.hh"

class Binding : public IModule
{
public:
  Binding();
  ~Binding();

  std::string			getName() const;
  int                           getType() const;
  void				launch();
};

#endif
