//
// Player.cpp for Player in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Mon Apr 25 22:03:38 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 23:12:12 2016 guillaume wilmot
//

#include <cmath>
#include <algorithm>
#include <unistd.h>
#include <dirent.h>
#include "Player.hpp"
#include "ClassicBomb.hpp"
#include "ScopedLock.hpp"
#include "Displayer.hpp"
#include "StopSleep.hpp"
#include "BombManager.hpp"
#include "ThreadManager.hpp"

Player::Player(int const id, double const x,
	       double const y, t_user *u_settings, std::vector<std::string> &skinList)
{
  _human = true;
  _id = id;
  _posX._var = x + 0.5;
  _posY._var = y + 0.5;
  _speed.set(1);
  _rangeBonus.set(0);
  _timerNewBomb = 3;
  _timerShield = 15;
  _shield = false;
  _alive._var = true;
  _curDirection = NONE;
  _done = true;
  _oldPos[0] = floor(y + 0.5);
  _oldPos[1] = floor(x + 0.5);
  _settings = u_settings;

  if (_settings == NULL)
    {
      if (instanciate3d("RANDOM", skinList) == -1)
	throw std::exception();
    }
  else
    {
      std::cout << "LOL MDR " << _settings->skin << std::endl;
      if (instanciate3d(_settings->skin, skinList) == -1)
	throw std::exception();
    }
  ClassicBomb	*bomb = new ClassicBomb();
  _bombs._var.push_back(bomb);
}

Player::~Player() {}

int			Player::instanciate3d(std::string const &skinName,
					      std::vector<std::string> &skinList)
{
  irr::scene::IAnimatedMesh             *mesh;
  irr::scene::IAnimatedMeshSceneNode    *player;
  irr::scene::ISceneManager		*smgr = Displayer::getSmgr();
  bool					set = false;
  std::string				newSkinName = "";

  if (!(mesh = smgr->getMesh("./assets/Perso/Steve.b3d")) ||
      !(player = smgr->addAnimatedMeshSceneNode(mesh)))
    return (-1);
  player->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
  if (skinName != "RANDOM")
    player->setMaterialTexture(0, Displayer::getDriver()->getTexture(std::string("./assets/Skins/" + skinName).c_str()));
  else
    {
      DIR				*dir;
      struct dirent			*ent;
      bool				isIn = false;
      unsigned int			i = 0;
      int				pass = 0;

      if ((dir = opendir("./assets/Skins/")) != NULL)
	{
	  while ((ent = readdir(dir)) != NULL)
	    {
	      i = 0;
	      while (i != skinList.size())
		{
		  if (ent->d_name == skinList[i++])
		    {
		      isIn = true;
		      pass = 1;
		      break ;
		    }
		}
	      if ((isIn == true && ent->d_name[0] != '.' && pass >= 2 && rand() % 2 == 0)
		  || (isIn == false && ent->d_name[0] != '.'))
		{
		  set = true;
		  newSkinName = ent->d_name;
		  player->setMaterialTexture(0, Displayer::getDriver()->getTexture(std::string("./assets/Skins/" + newSkinName).c_str()));
		  break ;
		}
	      ++pass;
	    }
	  if (set == false)
	    {
	      newSkinName = "Noob.png";
	      player->setMaterialTexture(0, Displayer::getDriver()->getTexture(std::string("./assets/Skins/Noob.png").c_str()));
	    }
	  closedir (dir);
	}
    }
  skinName != "RANDOM" ? skinList.push_back(skinName) : skinList.push_back(newSkinName);
  player->setPosition(irr::core::vector3df(SCALE_GAME * _posX.get(), 0, SCALE_GAME * _posY.get()));
  _steve = new Steve(player);
  return (0);
}

void			Player::move(irr::f32 frameDeltaTime)
{
  if (!_alive.get())
    return;

  irr::core::vector3df      position = _steve->getBlock()->getPosition();

  if (_curDirection == UP)
    position.Z -= 20.0 * frameDeltaTime * _speed.get();
  else if (_curDirection == DOWN)
    position.Z += 20.0 * frameDeltaTime * _speed.get();
  else if (_curDirection == RIGHT)
    position.X += 20.0 * frameDeltaTime * _speed.get();
  else if (_curDirection == LEFT)
    position.X -= 20.0 * frameDeltaTime * _speed.get();
  _steve->getBlock()->setPosition(position);
  _posY.set((position.Z / SCALE_GAME));
  _posX.set((position.X / SCALE_GAME));
  if ((_curDirection == UP && _posY.get() <= _oldPos[0] - 1) ||
      (_curDirection == DOWN && _posY.get() >= _oldPos[0] + 1) ||
      (_curDirection == RIGHT && _posX.get() >= _oldPos[1] + 1) ||
      (_curDirection == LEFT && _posX.get() <= _oldPos[1] - 1))
    {
      _done = true;
      _posX.set(floor(_posX.get()) + 0.5);
      _posY.set(floor(_posY.get()) + 0.5);
      _curDirection = NONE;
    }
  updatePos3d();
}

void			Player::reOrient()
{
  irr::core::vector3df	v;

  if (!_alive.get())
    return;
  v = _steve->getBlock()->getRotation();
  _steve->getBlock()->setRotation(irr::core::vector3df(v.X, ((static_cast<int>(_curDirection) + 1) * 90) % 360, v.Z));
  _steve->playAnim("walk");
}

void			Player::updatePos3d()
{
  if (_alive.get())
    _steve->getBlock()->setPosition(irr::core::vector3df(SCALE_GAME * _posX.get(), 0, SCALE_GAME * _posY.get()));
}

void			Player::updatePosReal()
{
  if (_alive.get())
    {
      _posX.set((_steve->getBlock()->getPosition().X / SCALE_GAME));
      _posY.set((_steve->getBlock()->getPosition().Z / SCALE_GAME));
    }
}

void			Player::addBomb()
{
  ScopedLock		lock(_bombs._mutex);

  _bombs._var.push_back(new ClassicBomb);
}

void			Player::PlaceBomb(Map &map)
{
  if (_bombs.get().size() > 0)
    {
      IBomb		*bomb;

      map.addItem(floor(_posX.get()), floor(_posY.get()), BOMB);
      bomb = _bombs.get().front();
      _bombs.get().pop_front();

      bomb->setX(_posX.get());
      bomb->setY(_posY.get());
      if (_end->get())
	return ;
      _steve->playAnim("putBomb");
      if (!_human)
	try {StoppableTimer t(0.4, _end);} catch (const std::exception &) {return ;}
      BombManager::get().addBomb(_rangeBonus.get(), bomb);

      if (_bombs.get().size() == 0)
	ThreadManager::get().addThread(new std::thread(getNewBomb, std::ref(*this), _end));
    }
}

void			Player::getNewBomb(Player &player, ProtectedVar<bool> *end)
{
  try
    {
      StoppableTimer	timer(player.getTimerNewBomb(), end);
    }
  catch (const std::exception &)
    {
      return ;
    }
  player.addBomb();
}

bool			Player::isWinner(Players &players)
{
  int			cnt = 0;

  for (unsigned int i = 0; i < players.getPlayers().size(); i++)
    {
      if (players.getPlayers()[i]->getAlive())
	++cnt;
    }
  if (cnt == 1)
    return true;
  return false;
}

bool			Player::isDead(Map &map)
{
  if (map.getMap()[std::abs(floor(_posY.get()))][std::abs(floor(_posX.get()))]->getItem() == BORDER)
    return (std::cout << "MORT MUR" << std::endl, true);
  if (map.getMap()[std::abs(floor(_posY.get()))][std::abs(floor(_posX.get()))]->getItem() == FIRE)
    {
      if (_shield == true)
	{
	  _shield = false;
	  return (false);
	}
      return (std::cout << "MORT FIRE" << std::endl, true);
    }
  return (false);
}
