//
// SpeedUp.cpp for SpeedUp in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:21:33 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 19:27:10 2016 guillaume wilmot
//

#include "SpeedUp.hh"
#include "Player.hpp"
#include "Displayer.hpp"
#include "MapError.hpp"

SpeedUp::SpeedUp(int const x, int const y) : PowerUp(x, y)
{

}

SpeedUp::~SpeedUp()
{

}

void		SpeedUp::PickedUp(Player *player) const
{
  double	s = player->getSpeed();

  player->setSpeed(s >= 2 ? s : s + 0.2);
}

void		SpeedUp::createItem()
{
  irr::scene::ISceneManager     *smgr = Displayer::getSmgr();
  irr::scene::IMesh		*mesh;

  if (!(mesh = smgr->getMesh("./assets/Powerups/Lighting/ItmThunder.obj")) ||
      !(_obj = smgr->addMeshSceneNode(mesh)))
    throw MapError("Error ./assets/Powerups/Lighting/itmThunder not found");
  _obj->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
}
