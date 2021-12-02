//
// HighScores.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:19:26 2016 Alban Combaud
//

#ifndef HIGHSCORES_HH_
# define HIGHSCORES_HH_

# include "IModule.hpp"
# include "Menu.hh"

class HighScores : public IModule
{
public:
  HighScores();
  ~HighScores();

  int                           getType() const;
  std::string			getName() const;
  void				launch();
};

#endif
