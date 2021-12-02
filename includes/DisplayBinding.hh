//
// DisplayBinding.hh for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:08 2016 Alban Combaud
// Last update Sun Jun  5 21:16:33 2016 Alban Combaud
//

#ifndef DISPLAYBINDING_HH_
# define DISPLAYBINDING_HH_

# include <vector>
# include "IModule.hpp"
# include "Menu.hh"

class DisplayBinding : public IModule
{
private:
  std::vector<std::string>		_keys;
  std::vector<CEGUI::PushButton *>	_buttons;
  CEGUI::FrameWindow			*_win;
public:
  DisplayBinding();
  ~DisplayBinding();

  std::string			getName() const;
  int                           getType() const;
  void				launch();
  void				createButtons();
  void				setButtons();
  void				setButton(CEGUI::PushButton *);

  bool				changeUpC1(const CEGUI::EventArgs &);
  bool				changeDownC1(const CEGUI::EventArgs &);
  bool				changeLeftC1(const CEGUI::EventArgs &);
  bool				changeRightC1(const CEGUI::EventArgs &);
  bool				changeDropC1(const CEGUI::EventArgs &);

  bool				changeUpC2(const CEGUI::EventArgs &);
  bool				changeDownC2(const CEGUI::EventArgs &);
  bool				changeLeftC2(const CEGUI::EventArgs &);
  bool				changeRightC2(const CEGUI::EventArgs &);
  bool				changeDropC2(const CEGUI::EventArgs &);
};

#endif
