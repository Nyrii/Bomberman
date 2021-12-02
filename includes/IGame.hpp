//
// IGame.hpp for IGame in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 13:33:38 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 23:37:02 2016 Nyrandone Noboud-Inpeng
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

# include <vector>
# include "ProtectedVar.hpp"
# include "Enum.hh"

class		IGame
{
public:
  virtual	~IGame() {};
  virtual void	init(int, int, ProtectedVar<bool> *, ProtectedVar<bool> *, std::vector<t_user *> &) = 0;
  virtual void	initPlayers() = 0;
  virtual void	launchGame() = 0;
};

#endif /* !IGAME_HPP_ */
