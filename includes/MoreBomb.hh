//
// MoreBomb.hh for MoreBomb in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:19:38 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 23:02:32 2016 guillaume wilmot
//

#ifndef MOREBOMB_HH_
# define MOREBOMB_HH_

# include "PowerUp.hh"

class		MoreBomb : public PowerUp
{
public:
  MoreBomb(int const, int const);
  ~MoreBomb();
  void		PickedUp(Player *) const;
  void		createItem();
};

#endif /* MOREBOMB_HH_ */
