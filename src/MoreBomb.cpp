//
// MoreBomb.cpp for MoreBomb in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:22:17 2016 Nyrandone Noboud-Inpeng
// Last update Sat Jun  4 19:45:03 2016 guillaume wilmot
//

#include "MoreBomb.hh"
#include "Player.hpp"
#include "MapError.hpp"
#include "Displayer.hpp"

MoreBomb::MoreBomb(int const x, int const y) : PowerUp(x, y) {}

MoreBomb::~MoreBomb() {}

void				MoreBomb::PickedUp(Player *player) const
{
  player->addBomb();
}

void				MoreBomb::createItem()
{
  irr::scene::ISceneManager	*smgr = Displayer::getSmgr();
  irr::scene::IMesh		*mesh;

  if (!(mesh = smgr->getMesh("./assets/Powerups/Bomb/Bomb.obj")) ||
     !(_obj = smgr->addMeshSceneNode(mesh)))
    throw MapError("Error ./assets/Powerups/Bomb.obj not found");
  _obj->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}
