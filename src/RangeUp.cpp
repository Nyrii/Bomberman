//
// RangeUp.cpp for RangeUp in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:20:12 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 19:14:44 2016 guillaume wilmot
//

#include "RangeUp.hh"
#include "Player.hpp"
#include "MapError.hpp"
#include "Displayer.hpp"

RangeUp::RangeUp(int const x, int const y) : PowerUp(x, y)
{

}

RangeUp::~RangeUp()
{

}

void		RangeUp::PickedUp(Player *player) const
{
  double	r = player->getRangeBonus();

  player->setRangeBonus(r + 1);
}

void		RangeUp::createItem()
{
  irr::scene::IMesh		*mesh;
  irr::scene::ISceneManager     *smgr = Displayer::getSmgr();

  if (!(mesh = smgr->getMesh("./assets/Powerups/Bow/Bow.obj")) ||
      !(_obj = smgr->addMeshSceneNode(mesh)))
    throw MapError("Error ./assets/Powerups/RangeUp.obj not found");
  _obj->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
}
