//
// DisplaySound.hh for  in /home/combau_a/rendu/cpp_indie_studio
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:19:16 2016 Alban Combaud
//

#ifndef DISPLAYNEWGAME_HH_
# define DISPLAYNEWGAME_HH_

# include "gui.hh"
# include "IModule.hpp"
# include "Menu.hh"
# include "Displayer.hpp"


class DisplayNewGame : public IModule
{
private:
  std::vector<t_user *>			_users;
  std::vector<CEGUI::Editbox	*>	_edit;
  std::vector<CEGUI::PushButton *>	_buttons;
  std::vector<CEGUI::PushButton *>	_left;
  std::vector<CEGUI::PushButton *>	_right;
  std::vector<CEGUI::PushButton *>	_close;
  std::vector<irr::scene::IAnimatedMeshSceneNode *>	_players;
  CEGUI::Spinner		        *_ia;
  bool					_go;
public:
  DisplayNewGame();
  ~DisplayNewGame();

  std::string			getName() const;
  int                           getType() const;
  void				launch();
  void				setButtons();
  void				init();
  void				deletePlayers();
  void				print_buttons();
  bool				changePlayer1(const CEGUI::EventArgs &);
  bool				changePlayer2(const CEGUI::EventArgs &);
  bool				changePlayer3(const CEGUI::EventArgs &);
  bool				changePlayer4(const CEGUI::EventArgs &);

  bool				statePlayer1Board1(const CEGUI::EventArgs &);
  bool				statePlayer1Board2(const CEGUI::EventArgs &);
  bool				statePlayer1Joy(const CEGUI::EventArgs &);

  bool				statePlayer1(const CEGUI::EventArgs &);
  bool				statePlayer2(const CEGUI::EventArgs &);
  bool				statePlayer3(const CEGUI::EventArgs &);
  bool				statePlayer4(const CEGUI::EventArgs &);

  bool				closePlayer1(const CEGUI::EventArgs &);
  bool				closePlayer2(const CEGUI::EventArgs &);
  bool				closePlayer3(const CEGUI::EventArgs &);
  bool				closePlayer4(const CEGUI::EventArgs &);

  bool				LaunchGame(const CEGUI::EventArgs &);

  void				changeLeftSkin(const int);
  void				changeRightSkin(const int);
  void				displaySkin(const int, const float, const float, const float);

  bool				leftPlayer1(const CEGUI::EventArgs &);
  bool				leftPlayer2(const CEGUI::EventArgs &);
  bool				leftPlayer3(const CEGUI::EventArgs &);
  bool				leftPlayer4(const CEGUI::EventArgs &);

  bool				rightPlayer1(const CEGUI::EventArgs &);
  bool				rightPlayer2(const CEGUI::EventArgs &);
  bool				rightPlayer3(const CEGUI::EventArgs &);
  bool				rightPlayer4(const CEGUI::EventArgs &);
};

#endif
