//
// Game.hh for Game in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 13:37:11 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 21:59:31 2016 guillaume wilmot
//

#ifndef GAME_HH_
# define GAME_HH_

# include <thread>
# include <unistd.h>
# include "IGame.hpp"
# include "Players.hh"
# include "Map.hh"

class		Game : public IGame
{
public:
  Game() {}
  ~Game() {}

  int		getTotalPlayers()		const {return (_totalPlayers);}
  int		getSuddenDeathY()		const {return (_suddenDeathY);}
  int		getSuddenDeathX()		const {return (_suddenDeathX);}
  Players	getPlayers()			const {return (_players);}
  Map		getMap()			const {return (_map);}

  void		setPlayers(Players &s)		      {_players = s;}

  void		init(int, int, ProtectedVar<bool> *, ProtectedVar<bool> *,
		     std::vector<t_user *> &);
  void		initPlayers();

  void		launchGame();
  int		start(const int, const int, std::vector<t_user *> &);

  void		suddenDeath(int, int, ProtectedVar<bool> *);
  void		randomBombs(Map &, Players &, ProtectedVar<bool> *);

  static void	timerSuddenDeath(Map &, Players &, ProtectedVar<bool> *);
  static void	launchPlay(Map &, Players &, Player *, ProtectedVar<bool> *, ProtectedVar<bool> *);
private:
  Game(Game const &);
  Game		&operator=(Game const &);

  int				_totalPlayers;
  int				_suddenDeathY;
  int				_suddenDeathX;
  ProtectedVar<bool>		*_end;
  ProtectedVar<bool>		*_start;
  Players			_players;
  Map				_map;
};

#endif /* !GAME_HH_ */
