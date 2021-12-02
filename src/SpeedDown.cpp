//
// SpeedDown.cpp for SpeedDown in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:21:49 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 16:47:39 2016 guillaume wilmot
//

#include "SpeedDown.hh"
#include "Player.hpp"
#include "Displayer.hpp"
#include "MapError.hpp"

SpeedDown::SpeedDown(int const x, int const y) : PowerUp(x, y)
{

}

SpeedDown::~SpeedDown()
{

}

void		SpeedDown::PickedUp(Player *player) const
{
  double	s = player->getSpeed();

  s = s <= 0.5 ? s : s > 1 ? s - 0.4 : s - 0.1;
  s = s < 0.5 ? 0.5 : s;
  player->setSpeed(s);
}

void		SpeedDown::createItem()
{
  irr::scene::ISceneManager     *smgr = Displayer::getSmgr();
  irr::scene::IMesh		*mesh;

  if (!(mesh = smgr->getMesh("./assets/Powerups/SpeedDown.obj")) ||
      !(_obj = smgr->addMeshSceneNode(mesh)))
    throw MapError("Error ./assets/Powerups/SpeedDown.obj not found");
  _obj->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
}
