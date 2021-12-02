//
// Map.hh for map in /home/milcen_a/C++/cpp_indie_studio
//
// Made by
// Login   <milcen_a@epitech.net>
//
// Started on  Mon Apr 25 21:32:31 2016
// Last update Sun Jun  5 03:42:03 2016 guillaume wilmot
//

#ifndef	MAP_HH_
# define MAP_HH_

# include <iostream>
# include <vector>
# include <utility>

# include "FireManager.hpp"
# include "Enum.hh"
# include "PowerUp.hh"
# include "Tile.hh"
# include "ProtectedVar.hpp"

class	Players;

class				Map
{
public:
  Map();
  ~Map();

  std::vector<std::vector<Tile *> >	&getMap();
  std::vector<std::vector<Tile *> >	&getDangerMap();
  std::vector<std::vector<Tile *> >	copyMap();

  char				getItem(int const, int const);
  int				getMaxX() const;
  int				getMaxY() const;
  std::vector<PowerUp *>	&getPowerUps();
  bool				isAnObstacle(int const, int const, Players &);
  int				getBeginPerimeter() const;

  void				setMap(std::vector<std::vector<Tile *>> const &);

  void				deletePowerup(int, int);
  void				generate(int, int, Players &, std::vector<t_user *> &);
  void				placeFirstPlayers(int &, int &, int &, int &,
						  Players &, std::vector<t_user *> &, std::vector<std::string> &);
  void				placeOtherPlayers(int &, int &, int &, int &,
						  Players &, std::vector<t_user *> &, std::vector<std::string> &);
  void				setFinalMap(Players &);
  void				compareBonusAndPlayerPos(Player &);

  void				destroyPos(const unsigned int, const unsigned int);
  void				addItem(const unsigned int, const unsigned int, Items const &);
  void				addPowerUp(int const, int const);
  void				print() const;
  void				destroy();

  void				removeDanger(int const, int const, int const);
  void				putDanger(int const, int const, int const);

private:
  std::vector<std::vector<Tile *> >	_map;
  std::vector<std::vector<Tile *> >	_dangerMap;
  int					_maxX;
  int					_maxY;
  int					_beginPerimeter;
  int					_endPerimeter;
  int					_nbPlayers;
  int					_minPowerUp;
  int					_maxPowerUp;
  int					_maxRandVal;
  int					_index;
  ProtectedVar<FireManager>		_fireMgr;
};

#endif /* !MAP_HH_ */
