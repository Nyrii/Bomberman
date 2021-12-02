//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:08:28 2016 Alban Combaud
//

# include "Back.hh"
# include "DisplayCredits.hh"
# include "gui.hh"
# include "ListScores.hh"
# include "Credits.hh"

DisplayCredits::DisplayCredits()
{
}

DisplayCredits::~DisplayCredits()
{
}

int	DisplayCredits::getType() const
{
  return 1;
}

std::string	DisplayCredits::getName() const
{
  Gui					*gui = Gui::getGui(NULL);
  CEGUI::DefaultWindow			*staticText = static_cast<CEGUI::DefaultWindow *>(gui->createWindow("AlfiskoSkin/Label", "", 0.425f, 0.05f, 0.15f, 0.1f));
  float					i;
  Credits				cred;
  std::vector<std::string>		tmp;
  float					size;

  i = 0.15f;
  cred.fetchCredits();
  tmp = cred.getCredits();
  for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
      size = 0.5 - (0.25);
      CEGUI::DefaultWindow *left = static_cast<CEGUI::DefaultWindow *>(gui->createWindow("AlfiskoSkin/Label", "", size, i, 0.50f, 0.05f));
      left->setText(*it);
      i += 0.05f;
    }
  staticText->setText("CREDITS");
  return std::string("DisplayCredits");
}

void		DisplayCredits::launch()
{
  return;
}
