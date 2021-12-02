//
// Game.cpp for Game in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 13:40:34 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 22:00:10 2016 guillaume wilmot
//

#include "MapError.hpp"
#include "GameError.hpp"
#include "StopSleep.hpp"
#include "ThreadManager.hpp"
#include "BombManager.hpp"
#include "Game.hpp"
#include "SuddenDeath.hpp"
#include "ClassicBomb.hpp"
#include "Displayer.hpp"
#include "Map.hh"
#include "Players.hh"
#include "gui.hh"
#include "Sdl.hpp"

void			Game::init(int nbIA, int nbNormalPlayer,
				   ProtectedVar<bool> *end,
				   ProtectedVar<bool> *start,
				   std::vector<t_user *> &u_settings)
{
  _totalPlayers = nbIA + nbNormalPlayer;
  _end = end;
  _start = start;

  for (unsigned int i = 0; i != u_settings.size(); i++)
    {
      if (u_settings[i] == NULL || u_settings[i]->status == false)
	u_settings.erase(u_settings.begin() + i--);
    }
  try
    {
      _map.generate(nbIA, nbNormalPlayer, _players, u_settings);
    }
  catch (const MapError &e)
    {
      std::cout << e.what() << std::endl;
      throw GameError("Error: Could not launch the game.");
    }
  BombManager::get().init(_end, _map);
  BombManager::get().setMe(new std::thread(BombManager::loop));
  ThreadManager::get().addThread(BombManager::get().getMe());
}

void			Game::initPlayers()
{
  int			i;
  std::vector<Player *>	players = _players.getPlayers();

  for (i = 0; i < players.size(); i++)
    {
      std::thread	*t;

      t = new std::thread(launchPlay,
			  std::ref(_map),
			  std::ref(_players),
			  players[i],
			  _start,
			  _end);
      ThreadManager::get().addThread(t);
    }
}

void			Game::launchPlay(Map &map, Players &players, Player *player,
					 ProtectedVar<bool> *start, ProtectedVar<bool> *end)
{
  SDL::get().playMusic(GAME_MUSIC);
  player->play(map, players, start, end);
}

void			Game::launchGame()
{
  ThreadManager::get().addThread(new std::thread(SuddenDeath::timerSuddenDeath, std::ref(_map), std::ref(_players), _end, _totalPlayers));
}

int			Game::start(const int nbIA, const int nbNormalPlayer,
				    std::vector<t_user *> &u_settings)
{
  int			ret;

  if (nbIA + nbNormalPlayer < 2)
    return (0);
  try {
    Displayer		displayer;
    ProtectedVar<bool>	end;
    ProtectedVar<bool>	startP;

    end.set(false);
    startP.set(false);

    init(nbIA, nbNormalPlayer, &end, &startP, u_settings);
    initPlayers();
    launchGame();

    displayer.setCaption(L"Bomberman");
    ret = displayer.display(*this, &end, &startP);
    end.set(true);
    ThreadManager::get().end();
    BombManager::get().clear();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return (std::cerr << "Quit" << std::endl, -1);
  } catch (...) {
    return (std::cerr << "Quit" << std::endl, -1);
  }
  return (ret);
}
