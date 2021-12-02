//
// ClassicBomb.hpp for ClassicBomb in /Users/noboud_n/Documents/Share/cpp_indie_studio/includes/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Wed Jun  1 13:18:35 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 10:13:19 2016 guillaume wilmot
//

#ifndef CLASSICBOMB_HPP_
# define CLASSICBOMB_HPP_

# include <thread>

# include <chrono>
# include "IBomb.hpp"
# include "Map.hh"

class		ClassicBomb : public IBomb {
public:
  ClassicBomb();
  ~ClassicBomb() {}

  int		getX()			const {return (_x);}
  int		getY()			const {return (_y);}
  float		getDetonationDelay()	const {return (_detonationDelay);}
  float		getClearDelay()		const {return (_clearDelay);}
  int		getRange()		const {return (_range);}
  bool		hasDetonated()		const {return (_detonated);}
  Bomb3d	*getBomb()		const {return (_bomb);}

  irr::scene::ISceneNode *getLight()				     const {return (_light);}
  std::chrono::high_resolution_clock::time_point	getPutTime() const {return (_putTime);}
  void		setPutTime(const std::chrono::high_resolution_clock::time_point s) {_putTime = s;}
  void		setLight(irr::scene::ISceneNode *s)				   {_light = s;}

  void		setBomb(Bomb3d *s)		      {_bomb = s;}
  void		setX(int s)			      {_x = s;}
  void		setY(int s)			      {_y = s;}
  void		setDetonationDelay(const float s)     {_detonationDelay = s;}
  void		setClearDelay(const float s)	      {_clearDelay = s;}
  void		setRange(const int s)		      {_range = s;}
  void		setDetonated(const bool s)	      {_detonated = s;}

  void	spread(Map &, int const, int const, int const);

  bool	spreadFireUp(Map &, int const, int const, int const) const;
  bool	spreadFireDown(Map &, int const, int const, int const) const;
  bool	spreadFireRight(Map &, int const, int const, int const) const;
  bool	spreadFireLeft(Map &, int const, int const, int const) const;

  void	clearFireUp(Map &, int const, int const, int const) const;
  void	clearFireDown(Map &, int const, int const, int const) const;
  void	clearFireRight(Map &, int const, int const, int const) const;
  void	clearFireLeft(Map &, int const, int const, int const) const;

private:

  ClassicBomb(const ClassicBomb &);
  ClassicBomb		&operator=(const ClassicBomb &);

  std::chrono::high_resolution_clock::time_point	_putTime;
  irr::scene::ISceneNode				*_light;

  Bomb3d		*_bomb;
  bool			_detonated;
  float			_detonationDelay;
  float			_clearDelay;
  int			_range;
  int			_x;
  int			_y;
};

#endif /* !CLASSICBOMB_HPP_ */
