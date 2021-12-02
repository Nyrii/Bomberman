//
// RangeDown.hh for RangeDown in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:16:30 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 23:07:34 2016 guillaume wilmot
//

#ifndef RANGEDOWN_HH_
# define RANGEDOWN_HH_

# include "PowerUp.hh"

class		RangeDown : public PowerUp
{
public:
  RangeDown(int const, int const);
  ~RangeDown();
  void		PickedUp(Player *) const;
  void		createItem();
};

#endif /* RANGEDOWN_HH_ */
