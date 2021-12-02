//
// Gui.cpp for  in /home/combau_a/rendu/test/save/irlich/newtest
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Sun May  1 11:39:56 2016 Alban Combaud
// Last update Sun Jun  5 21:31:59 2016 Alban Combaud
//

# include "gui.hh"
# include "EventHandler.hpp"
# include "Enum.hh"
# include "Sdl.hpp"

Gui::Gui() : _rend(NULL), _device(NULL), _driver(NULL), _press(irr::KEY_KEY_CODES_COUNT), _sceneManager(NULL), _context(NULL), _win(NULL)
{
}

Gui::~Gui()
{
}

void		Gui::init(int width, int height)
{
  if (_rend == NULL)
    {
      if (!(_device = irr::createDevice (irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 32, false, false, true, this)))
	return ;
      _device->getCursorControl ()->setVisible (false);
      _driver = _device->getVideoDriver ();
      _sceneManager = _device->getSceneManager();
      _rend = &CEGUI::IrrlichtRenderer::bootstrapSystem(*_device);
    }
  CEGUI::DefaultResourceProvider *rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
  rp->setResourceGroupDirectory ("schemes", "./ressources/schemes/");
  rp->setResourceGroupDirectory ("imagesets", "./ressources/imagesets/");
  rp->setResourceGroupDirectory ("fonts", "./ressources/fonts/");
  rp->setResourceGroupDirectory ("looknfeel", "./ressources/looknfeel/");
  CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
  CEGUI::Scheme::setDefaultResourceGroup("schemes");
  CEGUI::Font::setDefaultResourceGroup("fonts");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
  _context = &CEGUI::System::getSingleton().createGUIContext(_rend->getDefaultRenderTarget());
  _win = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "FIRST WIN");
  _context->setRootWindow(_win);
  this->loadSchemes("TaharezLook.scheme");
  this->loadSchemes("AlfiskoSkin.scheme");
  this->loadSchemes("Bind.scheme");
  this->loadSchemes("Plus.scheme");
  this->loadSchemes("Close.scheme");
  this->loadSchemes("Right.scheme");
  this->loadSchemes("Left.scheme");
  this->loadSchemes("Editbox.scheme");
  this->loadFonts("ARCADE_R");
  this->setMouseSkin("AlfiskoSkin/MouseArrow");
  this->showMouse(true);
}

void		Gui::destroy()
{
  CEGUI::System::getSingleton().destroyGUIContext(*_context);
  CEGUI::System::destroy();
  _rend = NULL;
}

void		Gui::display()
{
  _rend->beginRendering();
  _context->draw();
  _rend->endRendering();
}

void	Gui::loadFonts(const std::string &font)
{
  CEGUI::FontManager::getSingleton().createFromFile(font + ".font");
  _context->setDefaultFont(font);
}

void	Gui::loadSchemes(const std::string &scheme)
{
  CEGUI::SchemeManager::getSingleton().createFromFile(scheme);
}

CEGUI::Window	*Gui::createWindow(const std::string &scheme, const std::string &name,
				   float xPer, float yPer, float xPerSize, float yPerSize)
{
  CEGUI::Window	*tmp = CEGUI::WindowManager::getSingleton().createWindow(scheme, name);

  _win->addChild(tmp);
  tmp->setPosition(CEGUI::UVector2(CEGUI::UDim(xPer, 0), CEGUI::UDim(yPer, 0)));
  tmp->setSize(CEGUI::USize(CEGUI::UDim(xPerSize, 0), CEGUI::UDim(yPerSize, 0)));
  return tmp;
}

void		Gui::setMouseSkin(const std::string &skin)
{
  _context->getMouseCursor().setDefaultImage(skin);
}

void		Gui::showMouse(const bool &state)
{
  if (state)
    _context->getMouseCursor().show();
  else
    _context->getMouseCursor().hide();
}

CEGUI::Key::Scan IRRKeyToCEGUIKey(irr::EKEY_CODE key)
{
  using namespace CEGUI;
  switch (key)
    {
    case irr::KEY_BACK: return Key::Backspace;
    case irr::KEY_TAB: return Key::Tab;
    case irr::KEY_RETURN: return Key::Return;
    case irr::KEY_PAUSE: return Key::Pause;
    case irr::KEY_ESCAPE: return Key::Escape;
    case irr::KEY_SPACE: return Key::Space;
    case irr::KEY_DELETE: return Key::Delete;
    case irr::KEY_KEY_0: return Key::Zero;
    case irr::KEY_KEY_1: return Key::One;
    case irr::KEY_KEY_2: return Key::Two;
    case irr::KEY_KEY_3: return Key::Three;
    case irr::KEY_KEY_4: return Key::Four;
    case irr::KEY_KEY_5: return Key::Five;
    case irr::KEY_KEY_6: return Key::Six;
    case irr::KEY_KEY_7: return Key::Seven;
    case irr::KEY_KEY_8: return Key::Eight;
    case irr::KEY_KEY_9: return Key::Nine;
    case irr::KEY_KEY_A: return Key::A;
    case irr::KEY_KEY_B: return Key::B;
    case irr::KEY_KEY_C: return Key::C;
    case irr::KEY_KEY_D: return Key::D;
    case irr::KEY_KEY_E: return Key::E;
    case irr::KEY_KEY_F: return Key::F;
    case irr::KEY_KEY_G: return Key::G;
    case irr::KEY_KEY_H: return Key::H;
    case irr::KEY_KEY_I: return Key::I;
    case irr::KEY_KEY_J: return Key::J;
    case irr::KEY_KEY_K: return Key::K;
    case irr::KEY_KEY_L: return Key::L;
    case irr::KEY_KEY_M: return Key::M;
    case irr::KEY_KEY_N: return Key::N;
    case irr::KEY_KEY_O: return Key::O;
    case irr::KEY_KEY_P: return Key::P;
    case irr::KEY_KEY_Q: return Key::Q;
    case irr::KEY_KEY_R: return Key::R;
    case irr::KEY_KEY_S: return Key::S;
    case irr::KEY_KEY_T: return Key::T;
    case irr::KEY_KEY_U: return Key::U;
    case irr::KEY_KEY_V: return Key::V;
    case irr::KEY_KEY_W: return Key::W;
    case irr::KEY_KEY_X: return Key::X;
    case irr::KEY_KEY_Y: return Key::Y;
    case irr::KEY_KEY_Z: return Key::Z;
    case irr::KEY_NUMPAD0: return Key::Numpad0;
    case irr::KEY_NUMPAD1: return Key::Numpad1;
    case irr::KEY_NUMPAD2: return Key::Numpad2;
    case irr::KEY_NUMPAD3: return Key::Numpad3;
    case irr::KEY_NUMPAD4: return Key::Numpad4;
    case irr::KEY_NUMPAD5: return Key::Numpad5;
    case irr::KEY_NUMPAD6: return Key::Numpad6;
    case irr::KEY_NUMPAD7: return Key::Numpad7;
    case irr::KEY_NUMPAD8: return Key::Numpad8;
    case irr::KEY_NUMPAD9: return Key::Numpad9;
    case irr::KEY_MULTIPLY: return Key::Multiply;
    case irr::KEY_ADD: return Key::Add;
    case irr::KEY_SEPARATOR: return Key::Decimal;
    case irr::KEY_SUBTRACT: return Key::Subtract;
    case irr::KEY_DECIMAL: return Key::Decimal;
    case irr::KEY_DIVIDE: return Key::Divide;
    case irr::KEY_F1: return Key::F1;
    case irr::KEY_F2: return Key::F2;
    case irr::KEY_F3: return Key::F3;
    case irr::KEY_F4: return Key::F4;
    case irr::KEY_F5: return Key::F5;
    case irr::KEY_F6: return Key::F6;
    case irr::KEY_F7: return Key::F7;
    case irr::KEY_F8: return Key::F8;
    case irr::KEY_F9: return Key::F9;
    case irr::KEY_F10: return Key::F10;
    case irr::KEY_F11: return Key::F11;
    case irr::KEY_F12: return Key::F12;
    case irr::KEY_F13: return Key::F13;
    case irr::KEY_F14: return Key::F14;
    case irr::KEY_F15: return Key::F15;
    case irr::KEY_COMMA: return Key::Comma;
    case irr::KEY_MINUS: return Key::Minus;
    case irr::KEY_PERIOD: return Key::Period;
    case irr::KEY_NUMLOCK: return Key::NumLock;
    case irr::KEY_SCROLL: return Key::ScrollLock;
    case irr::KEY_LSHIFT: return Key::LeftShift;
    case irr::KEY_RSHIFT: return Key::RightShift;
    case irr::KEY_LCONTROL: return Key::LeftControl;
    case irr::KEY_RCONTROL: return Key::RightControl;
    case irr::KEY_END: return Key::End;
    case irr::KEY_HOME: return Key::Home;
    case irr::KEY_LEFT: return Key::ArrowLeft;
    case irr::KEY_UP: return Key::ArrowUp;
    case irr::KEY_RIGHT: return Key::ArrowRight;
    case irr::KEY_DOWN: return Key::ArrowDown;
    case irr::KEY_INSERT: return Key::Insert;
    case irr::KEY_MENU: return Key::AppMenu;
    case irr::KEY_LMENU: return Key::LeftAlt;
    case irr::KEY_RMENU: return Key::RightAlt;
    case irr::KEY_PRIOR: return Key::PageUp;
    case irr::KEY_NEXT: return Key::PageDown;
    default:                return Key::Unknown;
    }
}

bool		Gui::OnEvent(const irr::SEvent &e)
{
  CEGUI::utf32	translate;

  switch (e.EventType)
    {
    case irr::EET_MOUSE_INPUT_EVENT:
      _context->injectMousePosition(e.MouseInput.X, e.MouseInput.Y);
      (e.MouseInput.isMiddlePressed() ?
       _context->injectMouseButtonDown(CEGUI::MouseButton::MiddleButton) :
       _context->injectMouseButtonUp(CEGUI::MouseButton::MiddleButton));
      (e.MouseInput.isRightPressed() ?
       _context->injectMouseButtonDown(CEGUI::MouseButton::RightButton) :
       _context->injectMouseButtonUp(CEGUI::MouseButton::RightButton));
      (e.MouseInput.isLeftPressed() ?
       _context->injectMouseButtonDown(CEGUI::MouseButton::LeftButton) :
       _context->injectMouseButtonUp(CEGUI::MouseButton::LeftButton));
      break;
    case irr::EET_KEY_INPUT_EVENT:
      if (e.KeyInput.PressedDown)
	{
	  _press = e.KeyInput.Key;
	  translate = 0;
	  translate |= (((CEGUI::utf32)e.KeyInput.Char));
	  _context->injectChar(translate);
	  _context->injectKeyDown(IRRKeyToCEGUIKey(e.KeyInput.Key));
	}
      else
	_context->injectKeyUp(IRRKeyToCEGUIKey(e.KeyInput.Key));
      break;

    }
  if (EventHandler::get())
    EventHandler::get()->OnEvent(e);
  return false;
}

void	Gui::add_buttons(const std::vector<IModule *> &_mods, float i)
{
  i = 0.1;
  for (std::vector<IModule*>::const_iterator it = _mods.begin(); it != _mods.end(); ++it)
    {
      if ((*it)->getType() == 0)
	{
	  CEGUI::PushButton *button = static_cast<CEGUI::PushButton *>(createWindow("AlfiskoSkin/Button", "", 0.40f, i, 0.2f, 0.125f));
	  button->setText((*it)->getName());
	  button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&IModule::launch, *it));
	  i += 0.15;
	}
      else
	{
	  (*it)->getName();
	  i = 0.8;
	}
    }
}

void	Gui::playVideo(const std::string &video, e_sound sound, bool destroy)
{
  CvCapture* capture = cvCreateFileCapture(video.c_str());
  IplImage* frame = NULL;

  if(!capture)
    {
      std::cerr << "Error: cannot open video" << std::endl;
      return ;
    }
  double fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
  for (int i = 0; i != -1; ++i)
    {
      if(!(frame = cvQueryFrame(capture)))
	break;
      cvShowImage("Introduction",frame);
      if (i == 0)
	SDL::get().playSound(sound);
      if (cvWaitKey(fps) >= 0)
	break;
    }
  cvReleaseCapture(&capture);
  if (destroy)
    cvDestroyWindow("Introduction");
}

void		Gui::setPress(const irr::EKEY_CODE &tmp)
{
  _press = tmp;
}

////// GETTERS

irr::IrrlichtDevice		*Gui::getDevice() const { return _device; }
irr::video::IVideoDriver	*Gui::getDriver() const { return _driver; }
irr::scene::ISceneManager	*Gui::getSceneManager() const { return _sceneManager; }
CEGUI::IrrlichtRenderer		*Gui::getRend() const { return _rend; }
CEGUI::GUIContext		*Gui::getContext() const { return _context; }
irr::EKEY_CODE			Gui::getPress() const { return _press; }
CEGUI::Window			*Gui::getWin() const { return _win; }
