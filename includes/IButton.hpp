//
// IButton.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 13:06:28 2016 Alban Combaud
// Last update Sun May  8 16:56:16 2016 Alban Combaud
//

#ifndef IBUTTON_HH_
# define IBUTTON_HH_

# include <iostream>
# include <string>
# include <vector>

class Menu;

class IButton : public IModule
{
public:
  IButton(){};
  ~IButton(){};

  virtual std::string	getName() const = 0;
  virtual void				launch() const = 0;
};

#endif
