//
// Menu.hh for  in /home/combau_a/rendu/cpp_indie_studio
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:15:00 2016 Alban Combaud
//

#ifndef MENU_HH_
# define MENU_HH_

# define UNUSED __attribute__((unused))

# include <vector>
# include <map>
# include <Keycodes.h>
# include "IModule.hpp"
# include "Enum.hh"

class					Menu
{
private:
  float					_sound;
  std::map<Direction, irr::EKEY_CODE>	_p1;
  std::map<Direction, irr::EKEY_CODE>	_p2;
  std::vector<IModule *>		_mods;
  std::vector<t_user *>			_users;
  int					_ia;
public:
  Menu();
  ~Menu();

  void					setMods(IModule *);
  void					setSound(const float &);
  std::vector<IModule *>		getMods() const;
  float					getSound() const;
  void					setP1(const Direction &, const irr::EKEY_CODE &);
  void					setP2(const Direction &, const irr::EKEY_CODE &);
  std::map<Direction, irr::EKEY_CODE>	getP1() const;
  std::map<Direction, irr::EKEY_CODE>	getP2() const;
  void					setUsers(t_user *user);
  std::vector<t_user *>			getUsers() const;
  void					cleanUsers();
  void					setIa(const int &);
  int					getIa() const;
  void					init();

  bool					checkKeys(const irr::EKEY_CODE &tmp) const;
  void					changeMods(const std::vector<IModule *> &);
  void					initKeyCode();
  void					initUsers();

  static Menu				*getMenu(Menu *tmp)
  {
    static Menu		*_men = NULL;

    if (_men == NULL)
      _men = tmp;
    return _men;
  };
};

#endif
