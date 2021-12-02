//
// IA.hh for IA in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Mon Apr 25 22:30:17 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 21:46:42 2016 Nyrandone Noboud-Inpeng
//

#ifndef IA_HH_
# define IA_HH_

# include <vector>
# include <map>
# include "IBomb.hpp"
# include "Map.hh"
# include "Enum.hh"
# include "Players.hh"

class	PathFinding;

typedef struct	s_infos
{
  int		x;
  int		y;
  int		distance;
  Direction	dir;
}		t_infos;

class					IA : public Player
{
public:
  IA(int const, double const, double const, t_user *, std::vector<std::string> &);
  ~IA();

  Map					getMap() const;
  std::map<Modules, t_infos>		getModuleStates() const;
  std::vector<std::vector<Tile *>>	getFireMap() const;
  std::vector<std::vector<Tile *>>	getPositionMap() const;
  std::vector<std::vector<Tile *>>	getDirectionMap() const;
  std::map<Modules, int>		getTemplateCoeff() const;
  std::map<Modules, int>		getTmpCoeff() const;
  Player				*getPlayer();

  void				removeSimulation(Map &map) const;
  bool				isInRange(t_infos const &, Map &, Items const &, Player *);
  void				checkAndSetDirection(t_infos &, Map &, Players &, Modules const);
  void				initAttacker();
  void				initCollector();
  void				initRunner();
  void				initDestroyer();
  void				setTmpCoefficients();
  void				play(Map &, Players &, ProtectedVar<bool> *, ProtectedVar<bool> *);
  void				findBonus(Map &, PathFinding &, Players &);
  void				findPlayers(Map &, PathFinding &, Players &);
  void				breakWalls(Map &, PathFinding &, Players &);
  void				stayAwayFromOthers(Map &, Players &);
  bool				simulatePlaceBomb(Map &, Players &, int const, int const);
  void				simulateFire(Map &, int const, int const, int const) const;
  void				simulateDanger(Map &);
  Direction			runAway(Map &, Players &, const bool);
  void				calculWeight(int);
  void				findBestAction(Map &, Players &);
  bool				isInDanger(Map &, int const, int const);
  static bool			NearDistance(t_infos const &, t_infos const &);

private:
  Map					_map;
  std::map<Modules, int>		_templateCoeff;
  std::map<Modules, int>		_tmpCoeff;
  std::map<Modules, t_infos>		_moduleStates;
  std::vector<std::vector<Tile *>>	_positionMap;
  std::vector<std::vector<Tile *>>	_directionMap;
};

#endif /* IA_HH_ */
