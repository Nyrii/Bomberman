//
// Player.hh for Player in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Mon Apr 25 21:58:34 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 16:38:36 2016 Nyrandone Noboud-Inpeng
//

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <list>
# include <thread>
# include <vector>
# include <iostream>
# include "Steve.hpp"
# include "ProtectedVar.hpp"
# include "IBomb.hpp"
# include "Map.hh"
# include "IPlayer.hpp"
# include "Enum.hh"

class	Players;

class			Player : public IPlayer
{
public:
  Player(int const, double const, double const, t_user *, std::vector<std::string> &);
  ~Player();

  void			PlaceBomb(Map &);
  void			addBomb();
  virtual void		play(Map &, Players &, ProtectedVar<bool> *, ProtectedVar<bool> *end) {_end = end;}

  static void		getNewBomb(Player &, ProtectedVar<bool> *);

  void			updatePos3d();
  void			updatePosReal();
  void			reOrient();
  void			move(const irr::f32);

  std::list<IBomb *>	getBombs()		      {return (_bombs.get());}
  Direction		getCurDirection()	const {return (_curDirection);}
  Steve			*getSteve()		const {return (_steve);}
  IBomb			*getNextBomb()		      {return (_bombs.get().size() > 0 ?
							       _bombs.get().front() : NULL);}

  int			getId()			const {return (_id);}
  double		getPosX()		      {return (_posX.get());}
  double		getPosY()		      {return (_posY.get());}
  double		getSpeed()		      {return (_speed.get());}
  int			getRangeBonus()		      {return (_rangeBonus.get());}
  int			getTimerNewBomb()	const {return (_timerNewBomb);}
  int			getTimerShield()	const {return (_timerShield);}
  bool			getShield()		const {return (_shield);}
  bool			getAlive()		      {return (_alive.get());}
  t_user 		*getSettings()		      {return (_settings);}

  void			setId(int const src)	      {_id = src;}
  void			setPosX(double const src)     {_posX.set(src);}
  void			setPosY(double const src)     {_posY.set(src);}
  void			setSpeed(double const src)    {_speed.set(src);}
  void			setRangeBonus(int const src)  {_rangeBonus.set(src);}
  void			setShield(bool const src)     {_shield = src;}
  void			setAlive(bool const src)      {_alive.set(src);}
  void			setCurDirection(Direction const src)	      { _curDirection = src;}
  virtual bool		isWinner(Players &);
  virtual bool		isDead(Map &);

private:

  int			instanciate3d(std::string const &, std::vector<std::string> &);

protected:
  Player(Player &);
  Player		&operator=(Player &);

  ProtectedVar<std::list<IBomb *> >	_bombs;
  Steve					*_steve;
  ProtectedVar<bool>	*_end;
  ProtectedVar<bool>	_alive;
  ProtectedVar<double>	_posX;
  ProtectedVar<double>	_posY;
  ProtectedVar<double>	_speed;
  ProtectedVar<int>	_rangeBonus;
  bool			_human;
  bool			_shield;
  int			_id;
  int			_timerNewBomb;
  int			_timerShield;
  double		_oldPos[2];
  bool			_done;
  Direction		_curDirection;
  t_user		*_settings;
};

#endif /* !PLAYER_HH_ */
