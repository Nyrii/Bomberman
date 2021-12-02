//
// Shield.cpp for Shield in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Apr 30 18:22:04 2016 Nyrandone Noboud-Inpeng
// Last update Fri Jun  3 19:27:02 2016 guillaume wilmot
//

#include "Shield.hh"
#include "Player.hpp"
#include "ThreadManager.hpp"
#include "Displayer.hpp"
#include "MapError.hpp"

Shield::Shield(int const x, int const y) : PowerUp(x, y)
{

}

Shield::~Shield()
{

}

void		Shield::PickedUp(Player *player) const
{
  player->setShield(true);
}

void		Shield::createItem()
{
  irr::scene::ISceneManager     *smgr = Displayer::getSmgr();
  irr::scene::IMesh		*mesh;

  if (!(mesh = smgr->getMesh("./assets/Powerups/Shield/Shield.obj")) ||
      !(_obj = smgr->addMeshSceneNode(mesh)))
    throw MapError("Error ./assets/Powerups/Shield/Shield.obj not found");
  _obj->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}
