//
// FireManager.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 15 21:43:20 2016 guillaume wilmot
// Last update Sun Jun  5 21:49:00 2016 guillaume wilmot
//

#include "Displayer.hpp"
#include "FireManager.hpp"
#include "Scale.hh"

int		FireManager::init(const std::vector<std::vector<Tile *>> &map)
{
  if (!(_mesh = Displayer::getSmgr()->getMesh("./assets/Fire/Fire.md3")))
    return (-1);
  for (int i = 1; i < 33; i++)
    {
      irr::io::path tmp = "./assets/Fire/Fire";
      tmp += i;
      tmp += ".png";
      _textureArray.push_back(Displayer::getDriver()->getTexture(tmp));
    }
  _textureAnimator = Displayer::getSmgr()->createTextureAnimator(_textureArray, 60, true);
  for (unsigned int i = 0; i < map.size(); i++)
    {
      _fire.push_back(new std::vector<Fire *>);
      for (unsigned int j = 0; j < map[i].size(); j++)
	{
	  _fire[i]->push_back(newFire(i, j, Displayer::getSmgr()));
	  removeFire(i, j);
	}
    }
  return (0);
}

void		FireManager::putFire(int i, int j)
{
  if ((*_fire[i])[j])
    (*_fire[i])[j]->getBlock()->setVisible(true);
}

void		FireManager::removeFire(int i, int j)
{
  if ((*_fire[i])[j])
    {
      Displayer::getSmgrMutex().lock();
      (*_fire[i])[j]->getBlock()->setVisible(false);
      Displayer::getSmgrMutex().unlock();
    }
}

Fire		*FireManager::newFire(int i, int j, irr::scene::ISceneManager *smgr) const
{
  irr::scene::IAnimatedMeshSceneNode	*fireMesh;
  AnimatedBlock				*fire;

  if (!(fireMesh = smgr->addAnimatedMeshSceneNode(_mesh)))
    return (NULL);
  fireMesh->setScale(irr::core::vector3df(SCALE_GAME, SCALE_GAME, SCALE_GAME));
  fireMesh->setPosition(irr::core::vector3df(SCALE_GAME * i, 0, SCALE_GAME * j));
  fireMesh->addAnimator(_textureAnimator);
  fireMesh->setMaterialTexture(0, _textureArray[0]);
  fireMesh->setMaterialFlag(irr::video::EMF_LIGHTING, 0);
  fireMesh->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
  fireMesh->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
  return (new Fire(fireMesh));
}
