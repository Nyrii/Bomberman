//
// SpeedDown.hh for SpeedDown in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:18:06 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 23:11:55 2016 guillaume wilmot
//

#ifndef SPEEDDOWN_HH_
# define SPEEDDOWN_HH_

# include "PowerUp.hh"

class		SpeedDown : public PowerUp
{
public:
  SpeedDown(int const, int const);
  ~SpeedDown();
  void		PickedUp(Player *) const;
  void		createItem();
};

#endif /* SPEEDDOWN_HH_ */
