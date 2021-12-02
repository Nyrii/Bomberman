//
// FactoryPowerUps.hh for FactoryPowerUp in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 17:36:17 2016 Nyrandone Noboud-Inpeng
// Last update Sat Apr 30 20:27:08 2016 Nyrandone Noboud-Inpeng
//

#ifndef FACTORYPOWERUPS_HH_
# define FACTORYPOWERUPS_HH_

# include <map>
# include "Enum.hh"
# include "PowerUp.hh"

class				FactoryPowerUps
{
public:
  FactoryPowerUps();
  ~FactoryPowerUps();
  FactoryPowerUps(FactoryPowerUps const &);
  FactoryPowerUps		&operator=(FactoryPowerUps const &);

  PowerUp			*createPowerUp(int const, int const, Items const &);
  PowerUp			*rangeUp(int, int) const;
  PowerUp			*rangeDown(int, int) const;
  PowerUp			*speedUp(int, int) const;
  PowerUp			*speedDown(int, int) const;
  PowerUp			*shield(int, int) const;
  PowerUp			*moreBomb(int, int) const;
private:
  std::map<Items, PowerUp *(FactoryPowerUps::*)(int, int) const>	_funcPtr;
};

#endif /* !FACTORYPOWERUP_HH_ */
