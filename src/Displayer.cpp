//
// Displayer.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed Apr 27 10:47:57 2016 guillaume wilmot
// Last update Sun Jun  5 22:42:26 2016 guillaume wilmot
//

#include <stdexcept>
#include "ThreadManager.hpp"
#include "StopSleep.hpp"
#include "Displayer.hpp"
#include "Block.hpp"
#include "Steve.hpp"
#include "gui.hh"
#include "Sdl.hpp"
#include "ListScores.hh"

Displayer::Displayer()
{
  _device = Gui::getGui(NULL)->getDevice();
  EventHandler::get(&_receiver);
  _receiver.setJoysticksInfo(_device);
  _driver = _device->getVideoDriver();
  getDriver(_driver);
  _smgr = _device->getSceneManager();
  getSmgr(_smgr);
  _guienv = _device->getGUIEnvironment();
  _then = _device->getTimer()->getTime();
  _lastFPS = -1;
  _device->getCursorControl()->setVisible(false);
  _cameras = new CameraManager(_smgr, &_receiver);
  _axes = new AxesSceneNode(0, _smgr, 1);
  if (!(_skydome = _smgr->addSkyDomeSceneNode(_driver->getTexture("./assets/Skydome/skydomenight2.jpg"), 16, 8, 0.95f, 2.0f)))
    throw std::exception();
}

Displayer::~Displayer() {}

void				Displayer::setCaption(const irr::core::stringw &caption)
{
  _caption = caption;
}

void				Displayer::updatePlayers3d(Players &players)
{
  for (int i = 0; i < players.getPlayers().size(); i++)
    players.getPlayers()[i]->updatePos3d();
}

void				Displayer::updatePlayersObj(Players &players)
{
  for (int i = 0; i < players.getPlayers().size(); i++)
    players.getPlayers()[i]->updatePosReal();
}

void				Displayer::movePlayers(std::vector<Player *> const &IA,
						       const irr::f32 frameDeltaTime)
{
  for (int i = 0; i < IA.size(); i++)
    IA[i]->move(frameDeltaTime);
}

void				Displayer::instanciateLight(Map &map)
{
  irr::scene::ISceneNode *node = NULL;
  if (!(node = _smgr->addLightSceneNode(0, irr::core::vector3df(map.getMaxX() * SCALE_GAME, 50, map.getMaxY() * SCALE_GAME), irr::video::SColorf(1.0f, 1.0, 1.0f, 1.0f), 30.0f)))
    return ;
  irr::scene::ISceneNodeAnimator *anim = NULL;
  if (!(anim = _smgr->createFlyCircleAnimator (irr::core::vector3df(map.getMaxX() / 2 * SCALE_GAME, 50, map.getMaxY() / 2 * SCALE_GAME), 20.0f)))
    return ;
  node->addAnimator(anim);
  anim->drop();
  _smgr->setAmbientLight(irr::video::SColorf(0.5, 0.5, 0.5, 0));
}

void				Displayer::updateFPS()
{
  int				fps = _driver->getFPS();

  if (_lastFPS != fps)
    {
      irr::core::stringw	tmp(_caption);

      tmp += L" fps: ";
      tmp += fps;
      tmp += " | triangle: ";
      tmp += _driver->getPrimitiveCountDrawn();
      _device->setWindowCaption(tmp.c_str());
      _lastFPS = fps;
    }
}

int				Displayer::manageEvents(Players &players,
							std::vector<Player *> const &normalPlayers,
							std::vector<Player *> const &IA,
							Map map,
							ProtectedVar<bool> *end)
{
  static bool			start = false;
  const irr::f32		MOVEMENT_SPEED = 5.f;
  const irr::u32		now = _device->getTimer()->getTime();
  const irr::f32		frameDeltaTime = (irr::f32)(now - _then) / 1000.f;

  if (start)
    {
      _cameras->getCamera()->manageEvents(frameDeltaTime, map);
      movePlayers(IA, frameDeltaTime);
    }
  for (unsigned int i = 0; i < normalPlayers.size(); ++i)
    {
      if (normalPlayers[i]->isWinner(players))
	{
	  ListScores		listScores;
	  Score			score;
	  int			count = 0;

	  listScores.fillListScore();
	  listScores.sort();
	  score.setPseudo(normalPlayers[i]->getSettings()->user);
          for (unsigned int y = 0; y != map.getMap().size(); y++)
            {
              for (unsigned int x = 0; x != map.getMap()[y].size(); x++)
		{
		  if (map.getMap()[y][x]->getItem() == BORDER
		      || map.getMap()[y][x]->getItem() == UNBREAKABLE_WALL)
		    ++count;
		}
            }
	  score.setScore(players.getPlayers().size() * 10 + count * 5);
	  listScores.addScore(score);
	  end->set(true);
      	  break ;
      	}
      if (normalPlayers[i]->isDead(map) && normalPlayers[i]->getAlive())
      	{
      	  normalPlayers[i]->setAlive(false);
	  SDL::get().playSound(DEATH);
	  normalPlayers[i]->getSteve()->playAnim("die");
	  Displayer::getSmgrMutex().lock();
	  normalPlayers[i]->getSteve()->getBlock()->remove();
	  Displayer::getSmgrMutex().unlock();
	}
    }
  _then = now;
  start = true;
  return (0);
}

int				Displayer::display(Game &game, ProtectedVar<bool> *end, ProtectedVar<bool> *start)
{
  Players			players = game.getPlayers();
  Map				map;
  std::vector<Player *>		normalPlayers;
  std::vector<Player *>		IA;
  int				size = players.getPlayers().size() * 2 + 5;

  for (unsigned int i = 0; i != players.getPlayers().size(); i++)
    {
      if (players.getPlayers()[i]->getSettings() != NULL)
	normalPlayers.push_back(players.getPlayers()[i]);
      else
	IA.push_back(players.getPlayers()[i]);
    }
  map = game.getMap();
  _cameras->setPlayer(normalPlayers);
  _cameras->getCamera()->getCam()->setPosition(irr::core::vector3df((size / 2) * SCALE_GAME,
				size * SCALE_GAME, (size / 2) * SCALE_GAME));
  _cameras->getCamera()->getCam()->setTarget(irr::core::vector3df((size / 2) * SCALE_GAME,
				0, (size / 2) * SCALE_GAME));
  instanciateLight(map);
  _smgr->drawAll();
  _guienv->drawAll();
  _driver->endScene();
  start->set(true);
  while (_device->run() && !end->get())
    {
      _driver->beginScene(true, true, irr::video::SColor(255,100,150,255));
      _axes->render();
      updatePlayers3d(players);
      if (manageEvents(players, normalPlayers, IA, game.getMap(), end) == -1)
	end->set(true);
      updatePlayersObj(players);
      getSmgrMutex().lock();
      _smgr->drawAll();
      getSmgrMutex().unlock();
      _guienv->drawAll();
      _driver->endScene();
      updateFPS();
    }
  EventHandler::get(NULL, 1);
  if (_device->run())
    return (0);
  return (-1);
}
