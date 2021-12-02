//
// IBomb.hpp for IBomb in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Mon Apr 25 21:38:54 2016 Nyrandone Noboud-Inpeng
// Last update Thu Jun  2 10:13:11 2016 guillaume wilmot
//

#ifndef IBOMB_HPP_
# define IBOMB_HPP_

# include <chrono>
# include "Bomb3d.hpp"
# include "ProtectedVar.hpp"

class		Map;

class		IBomb
{
public:
  virtual		~IBomb() {};

  virtual int		getX() const = 0;
  virtual int		getY() const = 0;
  virtual float		getDetonationDelay() const = 0;
  virtual float		getClearDelay() const = 0;
  virtual int		getRange() const = 0;
  virtual bool		hasDetonated() const = 0;
  virtual Bomb3d	*getBomb() const = 0;

  virtual irr::scene::ISceneNode				*getLight() const = 0;
  virtual std::chrono::high_resolution_clock::time_point	getPutTime() const = 0;
  virtual void		setPutTime(std::chrono::high_resolution_clock::time_point) = 0;
  virtual void		setLight(irr::scene::ISceneNode *) = 0;

  virtual void		setBomb(Bomb3d *) = 0;
  virtual void		setX(int) = 0;
  virtual void		setY(int) = 0;
  virtual void		setDetonationDelay(float) = 0;
  virtual void		setClearDelay(float) = 0;
  virtual void		setRange(int) = 0;
  virtual void		setDetonated(bool) = 0;

  virtual bool		spreadFireUp(Map &, int const, int const, int const) const = 0;
  virtual bool		spreadFireDown(Map &, int const, int const, int const) const = 0;
  virtual bool		spreadFireRight(Map &, int const, int const, int const) const = 0;
  virtual bool		spreadFireLeft(Map &, int const, int const, int const) const = 0;

  virtual void		clearFireUp(Map &, int const, int const, int const) const = 0;
  virtual void		clearFireDown(Map &, int const, int const, int const) const = 0;
  virtual void		clearFireRight(Map &, int const, int const, int const) const = 0;
  virtual void		clearFireLeft(Map &, int const, int const, int const) const = 0;
};

#endif /* !IBOMB_HPP_ */
