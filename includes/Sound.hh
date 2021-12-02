//
// Sound.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:05:30 2016 Alban Combaud
//

#ifndef SOUND_HH_
# define SOUND_HH_

# include "IModule.hpp"
# include "Menu.hh"

class Sound : public IModule
{
private:
  float		_volume;
public:
  Sound();
  ~Sound();

  std::string			getName() const;
  int                           getType() const;
  void				launch();
  
  float		getVolume() const;
  void		setVolume(const float &);
};

#endif
