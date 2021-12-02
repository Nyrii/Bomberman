//
// EventHandler.hpp for  in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Tue Apr 26 17:31:35 2016 guillaume wilmot
// Last update Sun Jun  5 15:43:07 2016 guillaume wilmot
//

#ifndef EVENTHANDLER_HPP_
# define EVENTHANDLER_HPP_

# ifdef _MSC_VER
#  define _CRT_SECURE_NO_WARNINGS
#  pragma comment(lib, "Irrlicht.lib")
# endif

# include <vector>
# include "irrlicht.h"

class EventHandler : public irr::IEventReceiver {
public:
  ~EventHandler() {}
  EventHandler()
  {
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
      {
	KeyIsDown[i] = false;
	KeyWasPressed[i] = false;
      }
    _joystickState = std::vector<irr::SEvent::SJoystickEvent>(4);
  }

  static EventHandler	*get(EventHandler *e = NULL, bool r = false)
  {
    static EventHandler	*_e = NULL;
    if (e)
      _e = e;
    if (r)
      _e = NULL;
    return (_e);
  }

  const	irr::SEvent::SJoystickEvent			&GetJoystickState(int const index) const
    {
      return _joystickState[index];
    }

  irr::core::position2di getMouse() {_mouse = false; return (_cursor);}
  bool wasMouse() const {return (_mouse);}
  bool IsKeyDown(irr::EKEY_CODE keyCode) const {return (KeyIsDown[keyCode]);}
  bool WasKeyPressed(irr::EKEY_CODE keyCode) {bool tmp = KeyWasPressed[keyCode]; KeyWasPressed[keyCode] = false; return (tmp);}
  bool OnEvent(const irr::SEvent &event)
  {
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
      {
	_cursor = irr::core::position2di(event.MouseInput.X, event.MouseInput.Y);
	_mouse = true;
      }
    if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
      KeyWasPressed[event.KeyInput.Key] = true;
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
	&& _joystickInfo[event.JoystickEvent.Joystick].Axes >= 8)
	{
	  _joystickState[event.JoystickEvent.Joystick] = event.JoystickEvent;
	}
    return (false);
  }

  void	setJoysticksInfo(irr::IrrlichtDevice *device)
    {
      device->activateJoysticks(_joystickInfo);
    }

private:
  bool				KeyWasPressed[irr::KEY_KEY_CODES_COUNT];
  bool				KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  bool						_mouse;
  std::vector<irr::SEvent::SJoystickEvent>	_joystickState;
  irr::core::array<irr::SJoystickInfo>		_joystickInfo;
  irr::core::position2di				_cursor;
};

#endif /* EVENTHANDLER_HPP_ */
