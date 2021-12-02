//
// Credits.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:17:11 2016 Alban Combaud
//

#ifndef CREDITS_HH_
# define CREDITS_HH_

# include "IModule.hpp"
# include "Menu.hh"

class Credits : public IModule
{
private:
  std::vector<std::string>	_credits;
public:
  Credits();
  ~Credits();

  std::vector<std::string>	getCredits() const;
  std::string			getName() const;
  int                           getType() const;
  void				fetchCredits();
  void				launch();
};

#endif
