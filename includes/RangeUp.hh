//
// RangeUp.hh for RangeUp in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:14:45 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 23:08:25 2016 guillaume wilmot
//

#ifndef RANGEUP_HH_
# define RANGEUP_HH_

# include "PowerUp.hh"

class		RangeUp : public PowerUp
{
public:
  RangeUp(int const, int const);
  ~RangeUp();
  void		PickedUp(Player *) const;
  void		createItem();
};

#endif /* RANGEUP_HH_ */
