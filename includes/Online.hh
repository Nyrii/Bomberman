//
// Online.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Mon May  9 15:45:39 2016 Alban Combaud
//

#ifndef ONLINE_HH_
# define ONLINE_HH_

# include "IModule.hpp"
# include "Menu.hh"

class Online : public IModule
{
public:
  Online();
  ~Online();

  std::string			getName() const;
  int                           getType() const;
  void				launch();
  void				Display(Menu &);
};

#endif
