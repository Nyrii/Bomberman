//
// Shield.hh for Shield in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:18:54 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 23:10:07 2016 guillaume wilmot
//

#ifndef SHIELD_HH_
# define SHIELD_HH_

# include "PowerUp.hh"

class		Shield : public PowerUp
{
public:
  Shield(int const, int const);
  ~Shield();
  void		PickedUp(Player *) const;
  void		createItem();
};

#endif /* SHIELD_HH_ */
