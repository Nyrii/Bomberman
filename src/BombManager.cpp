//
// BombManager.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 29 02:58:44 2016 guillaume wilmot
// Last update Sun Jun  5 03:53:26 2016 guillaume wilmot
//

#include "Displayer.hpp"
#include "ScopedLock.hpp"
#include "BombManager.hpp"
#include "StopSleep.hpp"
#include "Sdl.hpp"

void		BombManager::clear()
{
  ScopedLock	lock(_bombs._mutex);

  _bombs._var.clear();
}

void		BombManager::addBomb(int bonus, IBomb *bomb)
{
  ScopedLock	lock(_bombs._mutex);

  bomb->setRange(bomb->getRange() + bonus);
  bomb->setPutTime(std::chrono::high_resolution_clock::now());
  _bombs._var.push_back(bomb);
  _map->putDanger(bomb->getX(), bomb->getY(), bomb->getRange() + 1);
  _map->getMap()[bomb->getY()][bomb->getX()]->setItem(BOMB);

  irr::scene::IAnimatedMesh             *mesh;
  irr::scene::IAnimatedMeshSceneNode    *tnt;
  irr::scene::ISceneManager             *smgr = Displayer::getSmgr();

  if (!(mesh = smgr->getMesh("./assets/Blocks/Tnt.obj")) ||
      !(tnt = smgr->addAnimatedMeshSceneNode(mesh)))
    return ;

  tnt->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
  tnt->setScale(irr::core::vector3df(SCALE_GAME, SCALE_GAME, SCALE_GAME));
  irr::core::vector3df                extent;

  extent = tnt->getTransformedBoundingBox().getExtent();
  tnt->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
  tnt->setPosition(irr::core::vector3df(SCALE_GAME * bomb->getX(),
					SCALE_GAME * 0,
					SCALE_GAME * bomb->getY()));
  SDL::get().playSound(PUTBOMB);
  bomb->setBomb(new Bomb3d(tnt));
}


void		BombManager::loop()
{
  unsigned int	i;

  while (!BombManager::get().getEnd()->get())
    {
      BombManager::get().getBombs()._mutex.lock();
      for (i = 0; i < BombManager::get().getBombs()._var.size(); i++)
	{
	  std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
	  IBomb			*bomb = BombManager::get().getBombs()._var[i];

	  if (std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count() >=
	      std::chrono::duration_cast<std::chrono::microseconds>(bomb->getPutTime().time_since_epoch()).count() +
	      static_cast<int>(bomb->getDetonationDelay() * 1000000) && !bomb->hasDetonated())
	      BombManager::get().detonateBomb(bomb);
	  if (std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count() >=
	      std::chrono::duration_cast<std::chrono::microseconds>(bomb->getPutTime().time_since_epoch()).count() +
	      static_cast<int>(bomb->getDetonationDelay() * 1000000 + bomb->getClearDelay() * 1000000))
	    {
	      BombManager::get().clearBomb(bomb);
	      Displayer::getSmgrMutex().lock();
	      bomb->getBomb()->getBlock()->remove();
	      delete bomb->getBomb();
	      BombManager::get().getBombs()._var.erase(BombManager::get().getBombs()._var.begin() + i--);

	      Displayer::getSmgrMutex().unlock();
	    }
	}
      BombManager::get().getBombs()._mutex.unlock();
      try {
	StoppableTimer	timer(0.1, BombManager::get().getEnd());
      } catch (const std::exception &) {
	return ;
      }
    }
}

void		BombManager::detonateBomb(IBomb *bomb)
{
  std::vector<bool>     stop = std::vector<bool> (4, false);

  SDL::get().playSound(EXPLODEBOMB);
  for (int i = 0; i <= bomb->getRange(); ++i)
    {
      if (!stop.at(0))
        stop.at(0) = bomb->spreadFireUp(*_map, bomb->getX(), bomb->getY(), i);
      if (!stop.at(1))
        stop.at(1) = bomb->spreadFireDown(*_map, bomb->getX(), bomb->getY(), i);
      if (!stop.at(2))
        stop.at(2) = bomb->spreadFireRight(*_map, bomb->getX(), bomb->getY(), i);
      if (!stop.at(3))
        stop.at(3) = bomb->spreadFireLeft(*_map, bomb->getX(), bomb->getY(), i);
    }
  bomb->setDetonated(true);
  bomb->setLight(Displayer::getSmgr()->addLightSceneNode(0, irr::core::vector3df(bomb->getX() * SCALE_GAME, 2, bomb->getY() * SCALE_GAME), irr::video::SColor(255, 102, 1, 1), 15.0f));
}

void		BombManager::clearBomb(IBomb *bomb)
{
  for (int i = 0; i <= bomb->getRange(); ++i)
    {
      bomb->clearFireUp(*_map, bomb->getX(), bomb->getY(), i);
      bomb->clearFireDown(*_map, bomb->getX(), bomb->getY(), i);
      bomb->clearFireRight(*_map, bomb->getX(), bomb->getY(), i);
      bomb->clearFireLeft(*_map, bomb->getX(), bomb->getY(), i);
    }
  _map->removeDanger(bomb->getX(), bomb->getY(), bomb->getRange() + 1);
  Displayer::getSmgrMutex().lock();
  if (bomb->getLight())
    bomb->getLight()->remove();
  Displayer::getSmgrMutex().unlock();
}
