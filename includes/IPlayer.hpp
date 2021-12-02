//
// IPlayer.hpp for IPlayer in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Fri Apr 29 11:20:37 2016 Nyrandone Noboud-Inpeng
// Last update Fri Jun  3 22:57:21 2016 Nyrandone Noboud-Inpeng
//

#ifndef IPLAYER_HPP_
# define IPLAYER_HPP_

# include "Enum.hh"

class			Map;
class			Players;

class			IPlayer
{
public:
  virtual		~IPlayer() {};
  virtual void		PlaceBomb(Map &) = 0;
  virtual void		addBomb() = 0;
  virtual void		play(Map &, Players &, ProtectedVar<bool> *, ProtectedVar<bool> *) = 0;
  virtual Direction	getCurDirection() const = 0;
  virtual bool		isWinner(Players &) = 0;
  virtual bool		isDead(Map &) = 0;
};

#endif /* !IPLAYER_HPP_ */
