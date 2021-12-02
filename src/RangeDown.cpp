//
// RangeDown.cpp for RangeDown in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:21:15 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 19:15:36 2016 guillaume wilmot
//

#include "RangeDown.hh"
#include "Player.hpp"
#include "MapError.hpp"
#include "Displayer.hpp"

RangeDown::RangeDown(int const x, int const y) : PowerUp(x, y)
{

}

RangeDown::~RangeDown()
{

}

void		RangeDown::PickedUp(Player *player) const
{
  double	r = player->getRangeBonus();

  player->setRangeBonus(r <= 1 ? r : r - 1);
}

void		RangeDown::createItem()
{
  irr::scene::ISceneManager	*smgr = Displayer::getSmgr();
  irr::scene::IMesh     *mesh;

  if (!(mesh = smgr->getMesh("./assets/Powerups/Slingshot/Slingshot.obj")) ||
      !(_obj = smgr->addMeshSceneNode(mesh)))
    throw MapError("Error ./assets/Powerups/Slingshot/Slingshot.obj not found");
  _obj->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
}
