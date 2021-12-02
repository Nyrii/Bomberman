//
// BombManager.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 29 02:58:48 2016 guillaume wilmot
// Last update Sun Jun  5 03:51:38 2016 guillaume wilmot
//

#ifndef BOMBMANAGER_HPP_
# define BOMBMANAGER_HPP_

# include <thread>
# include <vector>
# include "Map.hh"
# include "IBomb.hpp"

class		BombManager {
public:
  static BombManager	&get() {static BombManager _mgr; return (_mgr);}
  static void		loop();

  void			clear();
  void			init(ProtectedVar<bool> *end, Map &map) {_end = end; _map = &map;}
  void			addBomb(int, IBomb *);

  ProtectedVar<std::vector<IBomb *> >	&getBombs()	{return (_bombs);}
  ProtectedVar<bool>			*getEnd() const	{return (_end);}
  Map					*getMap() const	{return (_map);}
  std::thread				*getMe()  const {return (_me);}

  void					setMe(std::thread *s) {_me = s;}

private:

  BombManager() {};
  BombManager(const BombManager &);

  void			operator=(const BombManager &);
  void			detonateBomb(IBomb *);
  void			clearBomb(IBomb *);

  ProtectedVar<std::vector<IBomb *> >	_bombs;
  ProtectedVar<bool>			*_end;
  Map					*_map;
  std::thread				*_me;
};

#endif /* !BOMB_MANAGER */
