//
// IModule.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 13:06:28 2016 Alban Combaud
// Last update Sun Jun  5 21:10:48 2016 Alban Combaud
//

#ifndef IMODULE_HH_
# define IMODULE_HH_

# include <iostream>
# include <string>
# include <vector>

class Menu;

class IModule
{
public:
  IModule(){};
  ~IModule(){};

  virtual void				launch() = 0;
  virtual std::string			getName() const = 0;
  virtual int				getType() const = 0;
};

#endif
