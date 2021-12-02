//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 23:22:14 2016 guillaume wilmot
//

#include "Sdl.hpp"
#include <dirent.h>

#include "Back.hh"
#include "DisplayNewGame.hh"
#include "Back.hh"
#include "gui.hh"
#include "Game.hpp"
#include "Displayer.hpp"

DisplayNewGame::DisplayNewGame()
{
  _go = false;
  init();
  print_buttons();
  setButtons();
}

DisplayNewGame::~DisplayNewGame()
{
}

void				DisplayNewGame::setButtons()
{
  _buttons[0]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::changePlayer1, this));
  _buttons[1]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::changePlayer2, this));
  _buttons[2]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::changePlayer3, this));
  _buttons[3]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::changePlayer4, this));
  for (int i = 0; i < 4; ++i)
    {
      _left.push_back(NULL);
      _right.push_back(NULL);
      _close.push_back(NULL);
      _edit.push_back(NULL);
      _players.push_back(NULL);
    }
}

void				DisplayNewGame::init()
{
  std::vector<t_user *>		tmp = Menu::getMenu(NULL)->getUsers();
  int				i;

  i = 0;
  while (i < 4)
    {
      tmp[i]->status = false;
      _users.push_back(tmp[i]);
      i++;
    }
}

int				DisplayNewGame::getType() const
{
  return 2;
}

void				DisplayNewGame::print_buttons()
{
  Gui				*gui = Gui::getGui(NULL);
  Menu				*menu = Menu::getMenu(NULL);
  float				i;

  i = 0.0f;
  _buttons.clear();
  CEGUI::PushButton *NewGame = static_cast<CEGUI::PushButton *>(gui->createWindow("AlfiskoSkin/Button", "", 0.70f, 0.8f, 0.20f, 0.125f));
  NewGame->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::LaunchGame, this));
  NewGame->setText("LET'S GO");
  for (std::vector<t_user *>::const_iterator it = _users.begin(); it != _users.end(); ++it)
    {
      CEGUI::PushButton *button = static_cast<CEGUI::PushButton *>(gui->createWindow("Plus/Button", "", 0.15f + i, 0.4f, 0.10f, 0.13f));
      _buttons.push_back(button);
      i += 0.20f;
    }
  CEGUI::DefaultWindow *staticText = static_cast<CEGUI::DefaultWindow *>(gui->createWindow("AlfiskoSkin/Label", "", 0.05f, 0.775f, 0.10f, 0.1f));
  staticText->setText("[colour='FFFFFFFF']IA NUMBER");
  _ia = static_cast<CEGUI::Spinner*>(gui->createWindow("TaharezLook/Spinner", "", 0.15f, 0.8f, 0.1f, 0.075f));
  _ia->setTextInputMode(CEGUI::Spinner::FloatingPoint);
  _ia->setMinimumValue(0.0f);
  _ia->setMaximumValue(9.0f);
  _ia->setStepSize(1.0f);
  _ia->setCurrentValue(menu->getIa());
  setButtons();
}

std::string			DisplayNewGame::getName() const
{
  return std::string("DisplayNewGame");
}

void				DisplayNewGame::launch()
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);
  std::vector<IModule *>	tmp;

  gui->init();
  tmp.push_back(new Back(menu->getMods()));
  menu->changeMods(tmp);
  gui->add_buttons(menu->getMods(), 0.2);
}

bool				DisplayNewGame::changePlayer1(const CEGUI::EventArgs &)
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);

  _users[0]->status = true;
  _buttons[0]->setVisible(false);
  if (_edit[0] == NULL)
    {
      displaySkin(0, -0.7, -0.05, 0.6);
      _close[0] = static_cast<CEGUI::PushButton *>(gui->createWindow("Close/Button", "", 0.20f, 0.05f, 0.02f, 0.05f));
      _close[0]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::closePlayer1, this));
      _edit[0] = static_cast<CEGUI::Editbox*>(gui->createWindow("Editbox/Editbox", "", 0.05f, 0.125f, 0.175f, 0.05f));
      _left[0] = static_cast<CEGUI::PushButton *>(gui->createWindow("Left/Button", "", 0.05f, 0.3f, 0.05f, 0.15f));
      _left[0]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::leftPlayer1, this));
      _right[0] = static_cast<CEGUI::PushButton *>(gui->createWindow("Right/Button", "", 0.20f, 0.3f, 0.05f, 0.15f));
      _right[0]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::rightPlayer1, this));
      CEGUI::RadioButton* radioButton = static_cast<CEGUI::RadioButton*>(gui->createWindow("TaharezLook/RadioButton", "RadioKeyboard0", 0.05f, 0.5f, 0.2f, 0.1f));
      (_users[0]->control == Controller::KEYBOARD_1 ? radioButton->setSelected(true) : radioButton->setSelected(false));
      radioButton->setText("KEYBOARD_1");
      radioButton->setGroupID(0);
      radioButton = static_cast<CEGUI::RadioButton*>(gui->createWindow("TaharezLook/RadioButton", "RadioJoystick0", 0.05f, 0.575f, 0.2f, 0.1f));
      (_users[0]->control == Controller::JOYSTICK ? radioButton->setSelected(true) : radioButton->setSelected(false));
      radioButton->setText("Joystick");
      radioButton->setGroupID(0);
      _edit[0]->setText(menu->getUsers()[0]->user);
      _edit[0]->setMaxTextLength(14);
      _edit[0]->setReadOnly(false);
    }
  _close[0]->setVisible(true);
  _edit[0]->setVisible(true);
  _left[0]->setVisible(true);
  _right[0]->setVisible(true);
  _players[0]->setVisible(true);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioKeyboard0"))->setVisible(true);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick0"))->setVisible(true);
  return true;
}

bool				DisplayNewGame::changePlayer2(const CEGUI::EventArgs &)
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);

  _users[1]->status = true;
  _buttons[1]->setVisible(false);
  if (_edit[1] == NULL)
    {
      displaySkin(1, -0.25, -0.05, 0);
      _close[1] = static_cast<CEGUI::PushButton *>(gui->createWindow("Close/Button", "", 0.425f, 0.05f, 0.02f, 0.05f));
      _close[1]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::closePlayer2, this));
      _edit[1] = static_cast<CEGUI::Editbox*>(gui->createWindow("Editbox/Editbox", "", 0.275f, 0.125f, 0.175f, 0.05f));
      _left[1] = static_cast<CEGUI::PushButton *>(gui->createWindow("Left/Button", "", 0.275f, 0.3f, 0.05f, 0.15f));
      _left[1]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::leftPlayer2, this));
      _right[1] = static_cast<CEGUI::PushButton *>(gui->createWindow("Right/Button", "", 0.425f, 0.3f, 0.05f, 0.15f));
      _right[1]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::rightPlayer2, this));
      CEGUI::RadioButton* radioButton = static_cast<CEGUI::RadioButton*>(gui->createWindow("TaharezLook/RadioButton", "RadioKeyboard1bis", 0.275f, 0.5f, 0.2f, 0.1f));
      (_users[1]->control == Controller::KEYBOARD_2 ? radioButton->setSelected(true) : radioButton->setSelected(false));
      radioButton->setText("keyboard_2");
      radioButton->setGroupID(1);

      radioButton = static_cast<CEGUI::RadioButton*>(gui->createWindow("TaharezLook/RadioButton", "RadioJoystick1", 0.275f, 0.575f, 0.2f, 0.1f));
      radioButton->setGroupID(1);
      radioButton->setText("Joystick");
      (_users[1]->control == Controller::JOYSTICK ? radioButton->setSelected(true) : radioButton->setSelected(false));
      _edit[1]->setText(menu->getUsers()[1]->user);
      _edit[1]->setMaxTextLength(14);
      _edit[1]->setReadOnly(false);
    }
  _close[1]->setVisible(true);
  _edit[1]->setVisible(true);
  _left[1]->setVisible(true);
  _right[1]->setVisible(true);
  _players[1]->setVisible(true);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioKeyboard1bis"))->setVisible(true);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick1"))->setVisible(true);
  return true;
}

bool				DisplayNewGame::changePlayer3(const CEGUI::EventArgs &)
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);

  _users[2]->status = true;
  _buttons[2]->setVisible(false);
  if (_edit[2] == NULL)
    {
      displaySkin(2, 0.2, -0.05, 0.6);
      _close[2] = static_cast<CEGUI::PushButton *>(gui->createWindow("Close/Button", "", 0.65f, 0.05f, 0.02f, 0.05f));
      _close[2]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::closePlayer3, this));
      _edit[2] = static_cast<CEGUI::Editbox*>(gui->createWindow("Editbox/Editbox", "", 0.50f, 0.125f, 0.175f, 0.05f));
      _edit[2]->setText(menu->getUsers()[2]->user);
      _left[2] = static_cast<CEGUI::PushButton *>(gui->createWindow("Left/Button", "", 0.5f, 0.3f, 0.05f, 0.15f));
      _left[2]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::leftPlayer3, this));
      _right[2] = static_cast<CEGUI::PushButton *>(gui->createWindow("Right/Button", "", 0.65f, 0.3f, 0.05f, 0.15f));
      _right[2]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::rightPlayer3, this));
      CEGUI::RadioButton* radioButton = static_cast<CEGUI::RadioButton*>(gui->createWindow("TaharezLook/RadioButton", "RadioJoystick2", 0.50f, 0.5f, 0.2f, 0.1f));
      radioButton->setGroupID(2);
      (_users[2]->control == Controller::JOYSTICK ? radioButton->setSelected(true) : radioButton->setSelected(false));
      radioButton->setText("Joystick");
      _edit[2]->setMaxTextLength(14);
      _edit[2]->setReadOnly(false);
    }
  _close[2]->setVisible(true);
  _edit[2]->setVisible(true);
  _left[2]->setVisible(true);
  _right[2]->setVisible(true);
  _players[2]->setVisible(true);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick2"))->setVisible(true);
  return true;
}

bool				DisplayNewGame::changePlayer4(const CEGUI::EventArgs &)
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);

  _users[3]->status = true;
  _buttons[3]->setVisible(false);
  if (_edit[3] == NULL)
    {
      displaySkin(3, 0.65, -0.05, 0.6);
      _close[3] = static_cast<CEGUI::PushButton *>(gui->createWindow("Close/Button", "", 0.875f, 0.05f, 0.02f, 0.05f));
      _close[3]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::closePlayer4, this));
      _edit[3] = static_cast<CEGUI::Editbox*>(gui->createWindow("Editbox/Editbox", "", 0.725f, 0.125f, 0.175f, 0.05f));
      _edit[3]->setText(menu->getUsers()[3]->user);
      _left[3] = static_cast<CEGUI::PushButton *>(gui->createWindow("Left/Button", "", 0.725f, 0.3f, 0.05f, 0.15f));
      _left[3]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::leftPlayer4, this));
      _right[3] = static_cast<CEGUI::PushButton *>(gui->createWindow("Right/Button", "", 0.875f, 0.3f, 0.05f, 0.15f));
      _right[3]->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&DisplayNewGame::rightPlayer4, this));
      CEGUI::RadioButton* radioButton = static_cast<CEGUI::RadioButton*>(gui->createWindow("TaharezLook/RadioButton", "RadioJoystick3", 0.725f, 0.5f, 0.2f, 0.1f));
      radioButton->setGroupID(3);
      (_users[3]->control == Controller::JOYSTICK ? radioButton->setSelected(true) : radioButton->setSelected(false));
      radioButton->setText("Joystick");
      _edit[3]->setMaxTextLength(14);
      _edit[3]->setReadOnly(false);
    }
  _close[3]->setVisible(true);
  _edit[3]->setVisible(true);
  _left[3]->setVisible(true);
  _right[3]->setVisible(true);
  _players[3]->setVisible(true);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick3"))->setVisible(true);
  return true;
}

bool				DisplayNewGame::closePlayer1(const CEGUI::EventArgs &)
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);

  _users[0]->status = false;
  _buttons[0]->setVisible(true);
  _close[0]->setVisible(false);
  _edit[0]->setVisible(false);
  _left[0]->setVisible(false);
  _right[0]->setVisible(false);
  _players[0]->setVisible(false);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioKeyboard0"))->setVisible(false);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick0"))->setVisible(false);
}

bool				DisplayNewGame::closePlayer2(const CEGUI::EventArgs &)
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);

  _users[1]->status = false;
  _buttons[1]->setVisible(true);
  _close[1]->setVisible(false);
  _edit[1]->setVisible(false);
  _left[1]->setVisible(false);
  _right[1]->setVisible(false);
  _players[1]->setVisible(false);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioKeyboard1bis"))->setVisible(false);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick1"))->setVisible(false);
}

bool				DisplayNewGame::closePlayer3(const CEGUI::EventArgs &)
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);

  _users[2]->status = false;
  _buttons[2]->setVisible(true);
  _close[2]->setVisible(false);
  _edit[2]->setVisible(false);
  _left[2]->setVisible(false);
  _right[2]->setVisible(false);
  _players[2]->setVisible(false);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick2"))->setVisible(false);
}

bool				DisplayNewGame::closePlayer4(const CEGUI::EventArgs &)
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);


  _users[3]->status = false;
  _buttons[3]->setVisible(true);
  _close[3]->setVisible(false);
  _edit[3]->setVisible(false);
  _left[3]->setVisible(false);
  _right[3]->setVisible(false);
  _players[3]->setVisible(false);
  static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick3"))->setVisible(false);
}

bool				DisplayNewGame::LaunchGame(const CEGUI::EventArgs &)
{
  Menu				*menu = Menu::getMenu(NULL);
  Gui				*gui = Gui::getGui(NULL);
  int				count = 0;
  Game				game;

  if (_go)
    return (false);
  _go = true;
  (_users[0]->status ? ((static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioKeyboard0")))->isSelected() ?
			_users[0]->control = Controller::KEYBOARD_1 : _users[0]->control = Controller::JOYSTICK) : 0);
  (_users[1]->status ? ((static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioKeyboard1bis")))->isSelected() ?
			_users[1]->control = Controller::KEYBOARD_2 : _users[1]->control = Controller::JOYSTICK) : 0);
  (_users[2]->status && (static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick2")))->isSelected() ?
   _users[2]->control = Controller::JOYSTICK : 0);
  (_users[3]->status && (static_cast<CEGUI::RadioButton *>(gui->getWin()->getChild("RadioJoystick3")))->isSelected() ?
   _users[3]->control = Controller::JOYSTICK : 0);
  (_users[0]->status ? (_users[0]->user = _edit[0]->getText().c_str()) : "");
  (_users[1]->status ? (_users[1]->user = _edit[1]->getText().c_str()) : "");
  (_users[2]->status ? (_users[2]->user = _edit[2]->getText().c_str()) : "");
  (_users[3]->status ? (_users[3]->user = _edit[3]->getText().c_str()) : "");
  if (_users[0]->status && _users[0]->control == Controller::KEYBOARD_1)
    _users[0]->keycodes = menu->getP1();
  if (_users[1]->status && _users[1]->control == Controller::KEYBOARD_2)
    _users[1]->keycodes = menu->getP2();
  menu->setIa(_ia->getCurrentValue());
  menu->cleanUsers();
  menu->setUsers(_users[0]);
  menu->setUsers(_users[1]);
  menu->setUsers(_users[2]);
  menu->setUsers(_users[3]);
  for (int i = 0; i < 4; ++i)
    if (_users[i]->status == true)
      ++count;
  if (menu->getIa() + count > 9)
    menu->setIa(menu->getIa() - (menu->getIa() + count - 9));
  if (game.start(menu->getIa(), count, _users) == -1)
    {
      gui->destroy();
      _exit(EXIT_FAILURE);
    }
  SDL::get().playMusic(MENU_THEME);
  gui->getDevice()->closeDevice();
  _go = false;
  return (true);
}

void				DisplayNewGame::changeLeftSkin(const int i)
{
  DIR				*dir;
  struct dirent			*ent;
  struct dirent			*before = NULL;

  if ((dir = opendir("./assets/Skins/")) != NULL)
    {
      while ((ent = readdir(dir)) != NULL)
	{
	  if (std::string(ent->d_name) == _users[i]->skin)
	    {
	      if (before != NULL)
		_users[i]->skin = before->d_name;
	      closedir(dir);
	      return ;
	    }
	  if (ent->d_name[0] != '.')
	    before = ent;
	}
      closedir(dir);
    }
}

void				DisplayNewGame::changeRightSkin(const int i)
{
  DIR				*dir;
  struct dirent			*ent;
  struct dirent			*next = NULL;

  if ((dir = opendir("./assets/Skins/")) != NULL)
    {
      while ((ent = readdir(dir)) != NULL)
	{
	  if (std::string(ent->d_name) == _users[i]->skin)
	    {
	      while ((next = readdir(dir)) != NULL && next->d_name[0] == '.');
	      if (next != NULL && next->d_name[0] != '.')
		_users[i]->skin = next->d_name;
	      closedir(dir);
	      return ;
	    }
	}
      closedir(dir);
    }
}

void				DisplayNewGame::displaySkin(const int i, const float x, const float y, const float z)
{
  irr::scene::IAnimatedMesh             *mesh;
  irr::scene::ISceneManager             *smgr = Gui::getGui(NULL)->getSceneManager();
  bool                                  set = false;

  if (!(mesh = smgr->getMesh("./assets/Perso/Steve.b3d")) ||
      !(_players[i] = smgr->addAnimatedMeshSceneNode(mesh)))
    return ;
  _players[i]->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
  _players[i]->setMaterialTexture(0, Gui::getGui(NULL)->getDriver()->getTexture(std::string("./assets/Skins/" + _users[i]->skin).c_str()));
  _players[i]->setScale(irr::core::vector3df(0.05, 0.07, 0.05));
  _players[i]->setPosition(irr::core::vector3df(x, y, z));
  _players[i]->setRotation(irr::core::vector3df(0, 45, 0));
}

bool				DisplayNewGame::leftPlayer1(const CEGUI::EventArgs &)
{
  changeLeftSkin(0);
  _players[0]->remove();
  displaySkin(0, -0.7, -0.05, 0.6);
}

bool				DisplayNewGame::leftPlayer2(const CEGUI::EventArgs &)
{
  changeLeftSkin(1);
  _players[1]->remove();
  displaySkin(1, -0.25, -0.05, 0);
}

bool				DisplayNewGame::leftPlayer3(const CEGUI::EventArgs &)
{
  changeLeftSkin(2);
  _players[2]->remove();
  displaySkin(2, 0.2, -0.05, 0.6);
}

bool				DisplayNewGame::leftPlayer4(const CEGUI::EventArgs &)
{
  changeLeftSkin(3);
  _players[3]->remove();
  displaySkin(3, 0.65, -0.05, 0.6);
}

bool				DisplayNewGame::rightPlayer1(const CEGUI::EventArgs &)
{
  changeRightSkin(0);
  std::cout << "SKIN = " << _users[0]->skin << std::endl;
  _players[0]->remove();
  displaySkin(0, -0.7, -0.05, 0.6);
}

bool				DisplayNewGame::rightPlayer2(const CEGUI::EventArgs &)
{
  changeRightSkin(1);
  std::cout << "SKIN = " << _users[1]->skin << std::endl;
  _players[1]->remove();
  displaySkin(1, -0.25, -0.05, 0);
}

bool				DisplayNewGame::rightPlayer3(const CEGUI::EventArgs &)
{
    changeRightSkin(2);
    _players[2]->remove();
    displaySkin(2, 0.2, -0.05, 0.6);
}

bool				DisplayNewGame::rightPlayer4(const CEGUI::EventArgs &)
{
  changeRightSkin(3);
  _players[3]->remove();
  displaySkin(3, 0.65, -0.05, 0.6);
}

void				DisplayNewGame::deletePlayers()
{
  if (_players[0])
    _players[0]->remove();
  if (_players[1])
    _players[1]->remove();
  if (_players[2])
    _players[2]->remove();
  if (_players[3])
    _players[3]->remove();
}
