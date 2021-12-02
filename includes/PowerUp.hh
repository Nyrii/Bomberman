//
// PowerUp.hh for PowerUp in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 16:18:08 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 23:00:20 2016 guillaume wilmot
//

#ifndef POWERUP_HH_
# define POWERUP_HH_

# include "IPowerUp.hpp"
# include "irrlicht.h"

class		Player;

class		PowerUp
{
public:
  PowerUp(int const, int const);
  virtual	~PowerUp();
  PowerUp(PowerUp const &);
  PowerUp	&operator=(PowerUp const &);

  virtual void	PickedUp(Player *) const = 0;
  virtual void	createItem() = 0;
  irr::scene::IMeshSceneNode	*get3d() const;
  int		getPosX() const;
  int		getPosY() const;
protected:
  irr::scene::IMeshSceneNode	*_obj;
  int		_posX;
  int		_posY;
};

#endif /* !POWERUP_HH_ */
