//
// ISpecial.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 13:06:28 2016 Alban Combaud
// Last update Fri Apr 29 18:34:04 2016 Alban Combaud
//

#ifndef IMODULE_HH_
# define IMODULE_HH_

# include <iostream>
# include <string>
# include <vector>

class Menu;

class ISpecial
{
public:
  ISpecial(){};
  ~ISpecial(){};

  virtual void		display(Menu &) = 0;
};

#endif
