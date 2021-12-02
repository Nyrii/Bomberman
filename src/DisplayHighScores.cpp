//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
//
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
//
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:08:18 2016 Alban Combaud
//

# include "Back.hh"
# include "DisplayHighscores.hh"
# include "gui.hh"
# include "ListScores.hh"
# include "Sdl.hpp"

DisplayHighScores::DisplayHighScores()
{
}

DisplayHighScores::~DisplayHighScores()
{
}

int	DisplayHighScores::getType() const
{
  return 1;
}

std::string	DisplayHighScores::getName() const
{
  Gui					*gui = Gui::getGui(NULL);
  CEGUI::DefaultWindow *staticText = static_cast<CEGUI::DefaultWindow *>(gui->createWindow("AlfiskoSkin/Label", "", 0.45f, 0.05f, 0.20f, 0.1f));
  ListScores		list;
  std::vector<Score>	tmp;
  float			i;

  list.fillListScore();
  list.sort();
  tmp = list.getHighscores();
  i = 0.15f;
  for (std::vector<Score>::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
      CEGUI::DefaultWindow *left = static_cast<CEGUI::DefaultWindow *>(gui->createWindow("AlfiskoSkin/Label", "", 0.30f, i, 0.15f, 0.05f));
      CEGUI::DefaultWindow *right = static_cast<CEGUI::DefaultWindow *>(gui->createWindow("AlfiskoSkin/Label", "", 0.60f, i, 0.15f, 0.05f));
      left->setText((*it).getPseudo());
      right->setText(std::to_string((*it).getScore()));
      i += 0.05f;
    }
  staticText->setText("HIGHSCORES TOP 10");
  staticText->setProperty( "Alpha", "0.9" );
  staticText->setProperty("VertFormatting", "VertCentred");
  staticText->setProperty("HorzFormatting", "HorzCentred");
  return std::string("DisplayHighScores");
}

void		DisplayHighScores::launch()
{
  return ;
}
