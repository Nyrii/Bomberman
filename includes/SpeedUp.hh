//
// SpeedUp.hh for SpeedUp in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:17:39 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 23:10:29 2016 guillaume wilmot
//

#ifndef SPEEDUP_HH_
# define SPEEDUP_HH_

# include "PowerUp.hh"

class		SpeedUp : public PowerUp
{
public:
  SpeedUp(int const, int const);
  ~SpeedUp();
  void		PickedUp(Player *) const;
  void		createItem();
};

#endif /* SPEEDUP_HH_ */
