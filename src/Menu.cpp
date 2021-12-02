//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:24:50 2016 Alban Combaud
//

# include <dirent.h>

# include "Play.hh"
# include "HighScores.hh"
# include "Options.hh"
# include "Credits.hh"
# include "Quit.hh"
# include "Menu.hh"

Menu::Menu() : _sound(50.0), _ia(0)
{
  initKeyCode();
  initUsers();
  init();
}

Menu::~Menu()
{
}

void		Menu::init()
{
  _mods.clear();
  _mods.push_back(new Play);
  _mods.push_back(new HighScores);
  _mods.push_back(new Options);
  _mods.push_back(new Credits);
  _mods.push_back(new Quit);
}

void		Menu::initUsers()
{
  DIR				*dir;
  struct dirent			*ent;
  std::string			name;

  if (((dir = opendir("./assets/Skins/")) == NULL)
      || ((ent = readdir(dir)) == NULL))
    name = "";
  else
    name = ent->d_name;
  for (int i = 0; i < 4; ++i)
    {
      t_user	*user = new t_user;
      user->status = false;
      user->control = Controller::JOYSTICK;
      user->user = std::string("Player ") + std::to_string(i);
      user->skin = name;
      _users.push_back(user);
    }
}

std::map<Direction, irr::EKEY_CODE>	Menu::getP1() const
{
  return _p1;
}

std::map<Direction, irr::EKEY_CODE>	Menu::getP2() const
{
  return _p2;
}

void				Menu::initKeyCode()
{
  _p1.insert (std::pair<Direction,irr::EKEY_CODE>(UP,irr::EKEY_CODE::KEY_KEY_Z));
  _p1.insert (std::pair<Direction,irr::EKEY_CODE>(DOWN,irr::EKEY_CODE::KEY_KEY_S));
  _p1.insert (std::pair<Direction,irr::EKEY_CODE>(LEFT,irr::EKEY_CODE::KEY_KEY_Q));
  _p1.insert (std::pair<Direction,irr::EKEY_CODE>(RIGHT,irr::EKEY_CODE::KEY_KEY_D));
  _p1.insert (std::pair<Direction,irr::EKEY_CODE>(DROP,irr::EKEY_CODE::KEY_SPACE));

  _p2.insert (std::pair<Direction,irr::EKEY_CODE>(UP,irr::EKEY_CODE::KEY_UP));
  _p2.insert (std::pair<Direction,irr::EKEY_CODE>(DOWN,irr::EKEY_CODE::KEY_DOWN));
  _p2.insert (std::pair<Direction,irr::EKEY_CODE>(LEFT,irr::EKEY_CODE::KEY_LEFT));
  _p2.insert (std::pair<Direction,irr::EKEY_CODE>(RIGHT,irr::EKEY_CODE::KEY_RIGHT));
  _p2.insert (std::pair<Direction,irr::EKEY_CODE>(DROP,irr::EKEY_CODE::KEY_MENU));
}

void				Menu::changeMods(const std::vector<IModule *> &tmp)
{
  _mods.clear();
  for (std::vector<IModule *>::const_iterator it = tmp.begin(); it != tmp.end();++it)
    _mods.push_back(*it);
}

void		Menu::setMods(IModule *mod)
{
  _mods.push_back(mod);
}

std::vector<IModule *>	Menu::getMods() const
{
  return _mods;
}

void			Menu::setSound(const float &tmp)
{
  _sound = tmp;
}

float			Menu::getSound() const
{
  return _sound;
}

bool			Menu::checkKeys(const irr::EKEY_CODE &tmp) const
{
  if (tmp == irr::EKEY_CODE::KEY_ESCAPE)
    return (false);
  for (std::map<Direction, irr::EKEY_CODE>::const_iterator it = _p1.begin(); it != _p1.end();++it)
    {
      if (it->second == tmp)
	return false;
    }
  for (std::map<Direction, irr::EKEY_CODE>::const_iterator it = _p2.begin(); it != _p2.end();++it)
    {
      if (it->second == tmp)
	return false;
    }
  return true;
}

void					Menu::setP1(const Direction &key, const irr::EKEY_CODE &code)
{
  _p1[key] = code;
}

void					Menu::setP2(const Direction &key, const irr::EKEY_CODE &code)
{
  _p2[key] = code;
}

void					Menu::setUsers(t_user *user)
{
  _users.push_back(user);
}

std::vector<t_user *>			Menu::getUsers() const
{
  return _users;
}

void					Menu::setIa(const int &ia)
{
  _ia = ia;
}

int					Menu::getIa() const
{
  return _ia;
}

void					Menu::cleanUsers()
{
  _users.clear();
}
