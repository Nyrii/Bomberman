//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 22:02:06 2016 Alban Combaud
//

# include "Menu.hh"
# include "Back.hh"
# include "DisplayBinding.hh"
# include "gui.hh"

static const std::string Directions[ ] = 
  {
    "-",
    "Left Button",
    "Right Button",
    "Cancel",
    "Middle Button",
    "X Button 1",
    "X Button 2",
    "-",
    "Back",
    "Tab",
    "-",
    "-",
    "Clear",
    "Return",
    "-",
    "-",
    "Shift",
    "Control",
    "Menu",
    "Pause",
    "Capital",
    "Kana",
    "-",      
    "Junja",
    "Final",
    "Kanji",
    "-",
    "Escape",
    "Convert",
    "Nonconvert",
    "Accept",
    "Mode Change",
    "Space",
    "Priot",
    "Next",
    "End",
    "Home",
    "Left",
    "Up",
    "Right",
    "Down",
    "Select",
    "Print",
    "Execute",
    "Snapshot",
    "Insert",
    "Delete",
    "Help",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "Left Windows",
    "Right Windows",
    "Apps",
    "-",
    "Sleep",
    "Numpad 0",
    "Numpad 1",
    "Numpad 2",
    "Numpad 3",
    "Numpad 4",
    "Numpad 5",
    "Numpad 6",
    "Numpad 7",
    "Numpad 8",
    "Numpad 9",
    "Numpad *",
    "Numpad +",
    "Numpad /",
    "Numpad -",
    "Numpad .",
    "Numpad /",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "Num Lock",
    "Scroll Lock",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "Left Shift",
    "Right Shight",
    "Left Control",
    "Right Control",
    "Left Menu",
    "Right Menu",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "Plus",
    "Comma",
    "Minus",
    "Period",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "Attn",
    "CrSel",
    "ExSel",
    "Erase OEF",
    "Play",
    "Zoom",
    "PA1",
    "OEM Clear",
    "-"
  };

void			DisplayBinding::setButtons()
{
  _buttons[0]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeUpC1, this));
  _buttons[1]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeDownC1, this));
  _buttons[2]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeLeftC1, this));
  _buttons[3]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeRightC1, this));
  _buttons[4]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeDropC1, this));

  _buttons[5]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeUpC2, this));
  _buttons[6]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeDownC2, this));
  _buttons[7]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeLeftC2, this));
  _buttons[8]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeRightC2, this));
  _buttons[9]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayBinding::changeDropC2, this));
}

void			DisplayBinding::createButtons()
{
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  float					i = 0;
  std::map<Direction, irr::EKEY_CODE>	p1 = menu->getP1();
  std::map<Direction, irr::EKEY_CODE>	p2 = menu->getP2();

  for (std::vector<std::string>::const_iterator it = _keys.begin(); it != _keys.end(); ++it)
    {
      CEGUI::DefaultWindow *txt = static_cast<CEGUI::DefaultWindow *>(gui->createWindow("AlfiskoSkin/Label", "", 0.125f, 0.05f + i, 0.20f, 0.1f));
      txt->setText(*it);
      i += 0.10f;
    }
  i = 0;
  for (std::map<Direction, irr::EKEY_CODE>::const_iterator it = p1.begin(); it != p1.end(); ++it)
    {
      CEGUI::PushButton *button = static_cast<CEGUI::PushButton *>(gui->createWindow("Bind/Button", "", 0.375f, 0.05f + i, 0.20f, 0.1f));
      button->setText(Directions[it->second]);
      _buttons.push_back(button);
      i += 0.10f;
    }
  i = 0;
  for (std::map<Direction, irr::EKEY_CODE>::const_iterator it = p2.begin(); it != p2.end(); ++it)
    {
      CEGUI::PushButton *button = static_cast<CEGUI::PushButton *>(gui->createWindow("Bind/Button", "", 0.6f, 0.05f + i, 0.20f, 0.1f));
      button->setText(Directions[it->second]);
      _buttons.push_back(button);
      i += 0.10f;
    }
  _win = static_cast<CEGUI::FrameWindow *>(gui->createWindow("AlfiskoSkin/FrameWindow", "", 0.30f, 0.0f, 0.575f, 0.6f));
  _win->setDragMovingEnabled(false);
  _win->setRollupEnabled(false);
  _win->setVisible(false);
  _win->setCloseButtonEnabled(false);
  setButtons();
}

DisplayBinding::DisplayBinding()
{
  _keys.push_back("UP");
  _keys.push_back("DOWN");
  _keys.push_back("LEFT");
  _keys.push_back("RIGHT");
  _keys.push_back("DROP");
  createButtons();
}

DisplayBinding::~DisplayBinding()
{
}

int	DisplayBinding::getType() const
{
  return 1;
}

void		DisplayBinding::setButton(CEGUI::PushButton *button)
{
  _buttons.push_back(button);
}

std::string	DisplayBinding::getName() const
{
  return "DisplayBinding";
}

void		DisplayBinding::launch()
{
  Menu					*menu = Menu::getMenu(NULL);
  Gui					*gui = Gui::getGui(NULL);
  std::vector<IModule *>		tmp;

  gui->init();
  tmp.push_back(new Back(menu->getMods()));
  menu->changeMods(tmp);
  gui->add_buttons(menu->getMods(), 0.2);
}

bool				DisplayBinding::changeUpC1(const CEGUI::EventArgs &)
{
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 0, 0, 0));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[0]->setText(Directions[tmp]);
  menu->setP1(Direction::UP, tmp);
  _win->setVisible(false);
  return true;
}

bool				DisplayBinding::changeDownC1(const CEGUI::EventArgs &)
{
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 122, 122, 122));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[1]->setText(Directions[tmp]);
  menu->setP1(Direction::DOWN, tmp);
  _win->setVisible(false);
  return true;
}

bool				DisplayBinding::changeLeftC1(const CEGUI::EventArgs &){
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 122, 122, 122));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[2]->setText(Directions[tmp]);
  menu->setP1(Direction::LEFT, tmp);
  _win->setVisible(false);
  return true;
}

bool				DisplayBinding::changeRightC1(const CEGUI::EventArgs &){
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 122, 122, 122));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[3]->setText(Directions[tmp]);
  menu->setP1(Direction::RIGHT, tmp);
  _win->setVisible(false);
  return true;
}
bool				DisplayBinding::changeDropC1(const CEGUI::EventArgs &){
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 122, 122, 122));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[4]->setText(Directions[tmp]);
  menu->setP1(Direction::DROP, tmp);
  _win->setVisible(false);
  return true;
}

bool				DisplayBinding::changeUpC2(const CEGUI::EventArgs &){
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 122, 122, 122));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[5]->setText(Directions[tmp]);
  menu->setP2(Direction::UP, tmp);
  _win->setVisible(false);
  return true;
}

bool				DisplayBinding::changeDownC2(const CEGUI::EventArgs &){
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 122, 122, 122));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[6]->setText(Directions[tmp]);
  menu->setP2(Direction::DOWN, tmp);
  _win->setVisible(false);
  return true;
}

bool				DisplayBinding::changeLeftC2(const CEGUI::EventArgs &){
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 122, 122, 122));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[7]->setText(Directions[tmp]);
  menu->setP2(Direction::LEFT, tmp);
  _win->setVisible(false);
  return true;
}

bool				DisplayBinding::changeRightC2(const CEGUI::EventArgs &){
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 122, 122, 122));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[8]->setText(Directions[tmp]);
  menu->setP2(Direction::RIGHT, tmp);
  _win->setVisible(false);
  return true;
}

bool				DisplayBinding::changeDropC2(const CEGUI::EventArgs &){
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  irr::EKEY_CODE			tmp;

  _win->setVisible(true);
  _win->activate();
  gui->setPress(irr::KEY_KEY_CODES_COUNT);
  while (gui->getDevice()->run() && ((tmp = gui->getPress()) == irr::KEY_KEY_CODES_COUNT || !menu->checkKeys(tmp)))
    {
      gui->getDriver()->beginScene (true, true, irr::video::SColor (100, 122, 122, 122));
      gui->getSceneManager()->drawAll();
      gui->display();
      gui->getDriver()->endScene();
    }
  _buttons[9]->setText(Directions[tmp]);
  menu->setP2(Direction::DROP, tmp);
  _win->setVisible(false);
  return true;
}
