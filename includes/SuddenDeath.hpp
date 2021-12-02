//
// SuddenDeath.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Mon May 30 21:15:08 2016 guillaume wilmot
// Last update Sat Jun  4 00:26:18 2016 Nyrandone Noboud-Inpeng
//

#ifndef SUDDENDEATH_HPP_
# define SUDDENDEATH_HPP_

# include "Map.hh"
# include "Players.hh"
# include "ProtectedVar.hpp"

class		SuddenDeath {
public:
  SuddenDeath() {_x = 1; _y = 1;}
  ~SuddenDeath() {}

  static void	timerSuddenDeath(Map &, Players &, ProtectedVar<bool> *, int);
  void		randomBombs(Map &, Players &, ProtectedVar<bool> *, int);
  void		suddenDeath(int, int, Map &, Players &, ProtectedVar<bool> *);
  int		getX() const { return _x; };
  int		getY() const { return _y; };
  void		setTotalPlayers(int const total) {_totalPlayers = total;}

private:
  int		_x;
  int		_y;
  int		_totalPlayers;
};

#endif /* !SUDDENDEATH_HPP_ */
