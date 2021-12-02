//
// Enum.hh for enum in /home/milcen_a/C++/cpp_indie_studio
//
// Made by
// Login   <milcen_a@epitech.net>
//
// Started on  Mon Apr 25 23:47:33 2016
// Last update Thu Jun  2 18:15:09 2016 Alban Combaud
//

#ifndef ENUM_HH_
# define ENUM_HH_

# include <map>
# include "Keycodes.h"

enum	Modules
{
  BONUS = 0,
  PLAYERS,
  RUN,
  BREAKWALL
};

enum	Direction
{
  UNDEFINED = -1,
  UP,
  LEFT,
  DOWN,
  RIGHT,
  NONE,
  DROP
};

enum	Items
{
  EMPTY = '0',
  BORDER = '1',
  UNBREAKABLE_WALL = '2',
  BREAKABLE_WALL = '3',
  BOMB = '4',
  FIRE = '5',
  DANGEROUS = '6',
  PLAYER = '7',
  SIMULATIONDANGER = '8',

  RANGEUP = 'a',
  RANGEDOWN = 'b',
  SPEEDUP = 'c',
  SPEEDDOWN = 'd',
  SHIELD = 'e',
  MOREBOMB = 'f'
};

enum Controller
{
  KEYBOARD_1,
  KEYBOARD_2,
  JOYSTICK
};

typedef struct				s_user
{
  bool					status;
  std::string				user;
  Controller				control;
  std::string				skin;
  std::map<Direction, irr::EKEY_CODE>	keycodes;
}					t_user;


enum    e_sound
{
  MENU_THEME = 0,
  GAME_MUSIC,
  CREDITS_MUSIC,
  HIGHSCORES_MUSIC,
  PICKPOWERUP,
  EXPLODEBOMB,
  PUTBOMB,
  DEATH,
  FALLINGBLOCK,
  MUSIC_SPLASH,
  MUSIC_INTRO
};

#endif /* !ENUM_HH_ */
