//
// IPowerUp.hpp for IPowerUp in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 16:12:29 2016 Nyrandone Noboud-Inpeng
// Last update Sat Apr 30 17:13:49 2016 Nyrandone Noboud-Inpeng
//

#ifndef IPOWERUP_HPP_
# define IPOWERUP_HPP_

class		Player;

class		IPowerUp
{
public:
  virtual	~IPowerUp() {};
  virtual void	PickedUp(Player *) const = 0;
};

#endif /* !IPOWERUP_HPP_ */
