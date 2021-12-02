//
// Camera.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun Jun  5 12:59:35 2016 guillaume wilmot
// Last update Sun Jun  5 22:30:13 2016 guillaume wilmot
//

#include "Pause.hh"
#include "Camera.hpp"

int				Camera::manageEvents(const float frameDeltaTime,
						     Map &map)
{
  int                           x;
  int                           y;
  irr::core::vector3df          extent;

  for (unsigned int i = 0; i != _player.size(); i++)
    if (_player[i]->getAlive())
      {
        extent = _player[i]->getSteve()->getBlock()->getTransformedBoundingBox().getExtent();
	irr::core::vector3df    playerPosition = _player[i]->getSteve()->getBlock()->getPosition();
        const irr::SEvent::SJoystickEvent &joystickData = _receiver->GetJoystickState(i);
        const irr::f32          DEAD_ZONE = 0.25f;
	irr::f32                moveHorizontal = 0.f;
	irr::f32                moveVertical = 0.f;

        map.compareBonusAndPlayerPos(*_player[i]);
        if (_player[i]->getSettings() != NULL
            && (_player[i]->getSettings()->control == KEYBOARD_1
                || _player[i]->getSettings()->control == KEYBOARD_2)
            && _player[i]->getAlive()
            && _player[i]->getPosY() > 0 && _player[i]->getPosY() < map.getMaxY()
            && _player[i]->getPosX() > 0 && _player[i]->getPosX() < map.getMaxX())
          {
            bool                                tab[4];
            tab[0] = _receiver->IsKeyDown(_player[i]->getSettings()->keycodes[DOWN]);
            tab[1] = _receiver->IsKeyDown(_player[i]->getSettings()->keycodes[UP]);
            tab[2] = _receiver->IsKeyDown(_player[i]->getSettings()->keycodes[LEFT]);
            tab[3] = _receiver->IsKeyDown(_player[i]->getSettings()->keycodes[RIGHT]);
            if (tab[0])
              {
                y = floor(_player[i]->getPosY());
                x = floor((playerPosition.X - 20.0 * frameDeltaTime * _player[i]->getSpeed() - extent.X / 2) / SCALE_GAME);
                x = x <= 0 ? 0 : x;
                if ((map.getMap()[y][x]->getItem() != BORDER
		     && map.getMap()[y][x]->getItem() != UNBREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BOMB)
                    || (map.getMap()[y][x]->getItem() == BOMB && map.getMap()[floor(_player[i]->getPosY())][floor(_player[i]->getPosX())]->getItem() == BOMB))
                  playerPosition.X -= 20.0 * frameDeltaTime * _player[i]->getSpeed();
                _player[i]->setCurDirection(LEFT);
                _player[i]->reOrient();
              }
            else if (tab[1])
              {
                y = floor(_player[i]->getPosY());
                x = floor((playerPosition.X + 20.0 * frameDeltaTime * _player[i]->getSpeed() + extent.X / 2) / SCALE_GAME);
                x = x >= map.getMaxY() ? map.getMaxY() : x;
                if ((map.getMap()[y][x]->getItem() != BORDER
		     && map.getMap()[y][x]->getItem() != UNBREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BOMB)
                    || (map.getMap()[y][x]->getItem() == BOMB && map.getMap()[floor(_player[i]->getPosY())][floor(_player[i]->getPosX())]->getItem() == BOMB))
                  playerPosition.X += 20.0 * frameDeltaTime * _player[i]->getSpeed();
                _player[i]->setCurDirection(RIGHT);
                _player[i]->reOrient();
              }
            if (tab[2])
              {
                y = floor((playerPosition.Z + 20.0 * frameDeltaTime * _player[i]->getSpeed() + extent.Z / 2) / SCALE_GAME);
                x = floor(_player[i]->getPosX());
                y = y >= map.getMaxX() ? map.getMaxX() : y;
                if ((map.getMap()[y][x]->getItem() != BORDER
		     && map.getMap()[y][x]->getItem() != UNBREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BOMB)
                    || (map.getMap()[y][x]->getItem() == BOMB && map.getMap()[floor(_player[i]->getPosY())][floor(_player[i]->getPosX())]->getItem() == BOMB))
                  playerPosition.Z += 20.0 * frameDeltaTime * _player[i]->getSpeed();
                _player[i]->setCurDirection(UP);
                _player[i]->reOrient();
	      }
            else if (tab[3])
              {
                y = floor((playerPosition.Z - 20.0 * frameDeltaTime * _player[i]->getSpeed() - extent.Z / 2) / SCALE_GAME);
                x = floor(_player[i]->getPosX());
                y = y <= 0 ? 0 : y;
                if ((map.getMap()[y][x]->getItem() != BORDER
		     && map.getMap()[y][x]->getItem() != UNBREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BOMB)
                    || (map.getMap()[y][x]->getItem() == BOMB && map.getMap()[floor(_player[i]->getPosY())][floor(_player[i]->getPosX())]->getItem() == BOMB))
                  playerPosition.Z -= 20.0 * frameDeltaTime * _player[i]->getSpeed();
                _player[i]->setCurDirection(DOWN);
                _player[i]->reOrient();
              }
            else if (_receiver->IsKeyDown(_player[i]->getSettings()->keycodes[DROP]))
              {
                _player[i]->PlaceBomb(map);
              }
            if (!tab[0] && !tab[1] && !tab[2] && !tab[3])
              _player[i]->getSteve()->playAnim("idle");
          }
        else if (_player[i]->getAlive())
          {
            moveHorizontal = static_cast<irr::f32>(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X]) / -32767.f;
            moveVertical = static_cast<irr::f32>(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y]) / -32767.f;
            if (fabs(moveHorizontal) < DEAD_ZONE && fabs(moveVertical) < DEAD_ZONE)
              _player[i]->getSteve()->playAnim("idle");
            else if (moveHorizontal < 0.f && fabs(moveHorizontal) > fabs(moveVertical))
              {
                y = floor((playerPosition.Z + moveHorizontal * 20.0 * frameDeltaTime * _player[i]->getSpeed() - extent.Z / 2) / SCALE_GAME);
                x = floor(_player[i]->getPosX());
                y = y <= 0 ? 0 : y;
                if ((map.getMap()[y][x]->getItem() != BORDER
                     && map.getMap()[y][x]->getItem() != UNBREAKABLE_WALL
                     && map.getMap()[y][x]->getItem() != BREAKABLE_WALL
                     && map.getMap()[y][x]->getItem() != BOMB)
                    || (map.getMap()[y][x]->getItem() == BOMB && map.getMap()[floor(_player[i]->getPosY())][floor(_player[i]->getPosX())]->getItem() == BOMB))
                  playerPosition.Z += moveHorizontal * 20.0 * frameDeltaTime * _player[i]->getSpeed();
                _player[i]->setCurDirection(UP);
                _player[i]->reOrient();
	      }
	    else if (moveHorizontal > 0.f && fabs(moveHorizontal) > fabs(moveVertical))
	      {
		y = floor((playerPosition.Z + moveHorizontal * 20.0 * frameDeltaTime * _player[i]->getSpeed() + extent.Z / 2) / SCALE_GAME);
		x = floor(_player[i]->getPosX());
		y = y <= 0 ? 0 : y;
		if ((map.getMap()[y][x]->getItem() != BORDER
		     && map.getMap()[y][x]->getItem() != UNBREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BOMB)
                    || (map.getMap()[y][x]->getItem() == BOMB && map.getMap()[floor(_player[i]->getPosY())][floor(_player[i]->getPosX())]->getItem() == BOMB))
		  playerPosition.Z += moveHorizontal * 20.0 * frameDeltaTime * _player[i]->getSpeed();
		_player[i]->setCurDirection(DOWN);
		_player[i]->reOrient();
	      }
	    else if (moveVertical < 0.f && fabs(moveVertical) > fabs(moveHorizontal))
	      {
		y = floor(_player[i]->getPosY());
		x = floor((playerPosition.X + moveVertical * 20.0 * frameDeltaTime * _player[i]->getSpeed() - extent.X / 2) / SCALE_GAME);
		x = x >= map.getMaxY() ? map.getMaxY() : x;
		if ((map.getMap()[y][x]->getItem() != BORDER
		     && map.getMap()[y][x]->getItem() != UNBREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BOMB)
                    || (map.getMap()[y][x]->getItem() == BOMB && map.getMap()[floor(_player[i]->getPosY())][floor(_player[i]->getPosX())]->getItem() == BOMB))
		  playerPosition.X += moveVertical * 20.0 * frameDeltaTime * _player[i]->getSpeed();
		_player[i]->setCurDirection(LEFT);
		_player[i]->reOrient();
	      }
	    else if (moveVertical > 0.f && fabs(moveVertical) > fabs(moveHorizontal))
	      {
		y = floor(_player[i]->getPosY());
		x = floor((playerPosition.X + 20.0 * frameDeltaTime * _player[i]->getSpeed() + extent.X / 2) / SCALE_GAME);
		x = x >= map.getMaxY() ? map.getMaxY() : x;
		if ((map.getMap()[y][x]->getItem() != BORDER
		     && map.getMap()[y][x]->getItem() != UNBREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BREAKABLE_WALL
		     && map.getMap()[y][x]->getItem() != BOMB)
                    || (map.getMap()[y][x]->getItem() == BOMB && map.getMap()[floor(_player[i]->getPosY())][floor(_player[i]->getPosX())]->getItem() == BOMB))
		  playerPosition.X += moveVertical * 20.0 * frameDeltaTime * _player[i]->getSpeed();
		_player[i]->setCurDirection(RIGHT);
		_player[i]->reOrient();
	      }
	    if (joystickData.IsButtonPressed(5))
	      _player[i]->PlaceBomb(map);
	  }
	_player[i]->getSteve()->getBlock()->setPosition(playerPosition);
	if (_player.size() == 1)
	  putCam(playerPosition);
	map.compareBonusAndPlayerPos(*_player[i]);
      }
  if (_player.size() == 1 && _player[0]->getAlive())
    if (_receiver->WasKeyPressed(irr::KEY_KEY_E))
      _manager->switchCamera(_player[0]->getSteve()->getBlock());
  if (_receiver->WasKeyPressed(irr::KEY_ESCAPE))
    return (-1);
  return (0);
}
