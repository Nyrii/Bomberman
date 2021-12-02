//
// Players.hh for Players in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Wed Apr 27 11:36:22 2016 Nyrandone Noboud-Inpeng
// Last update Tue May 31 14:22:56 2016 Nyrandone Noboud-Inpeng
//

#ifndef PLAYERS_HH_
# define PLAYERS_HH_

# include <vector>
# include "Player.hpp"
# include "ProtectedVar.hpp"

class			Players {
public:
  Players();
  ~Players();
  Players		&operator=(Players &);

  void			addPlayer(Player * const);
  void			removePlayer(Player const &);
  std::vector<Player *>	getPlayers();
  int			getLastPlayers();
  void			setPlayers(std::vector<Player *> const &);
private:
  ProtectedVar<std::vector<Player *> >	_players;
};

#endif /* !PLAYERS_HH_ */
