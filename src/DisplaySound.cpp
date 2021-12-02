//
// Menu.cpp for  in /home/combau_a/rendu/cpp_indie_studio
// 
// Made by Alban Combaud
// Login   <combau_a@epitech.net>
// 
// Started on  Tue Apr 26 11:02:14 2016 Alban Combaud
// Last update Sun Jun  5 21:25:16 2016 Alban Combaud
//

# include "Back.hh"
# include "DisplaySound.hh"
# include "Back.hh"
# include "gui.hh"

DisplaySound::DisplaySound()
{
}

DisplaySound::~DisplaySound()
{
}

int	DisplaySound::getType() const
{
  return 1;
}

std::string	DisplaySound::getName() const
{
  Gui					*gui = Gui::getGui(NULL);
  Menu					*menu = Menu::getMenu(NULL);
  CEGUI::Slider				*slider = static_cast<CEGUI::Slider*>(gui->createWindow("AlfiskoSkin/HorizontalSlider", "", 0.375f, 0.05f, 0.25f, 0.1f));

  static_cast<Back *>(menu->getMods()[1])->setSlider(slider);
  slider->setMaxValue(100.0f);
  slider->setClickStep(0.0f);
  slider->setCurrentValue(menu->getSound());
  CEGUI::DefaultWindow *staticText = static_cast<CEGUI::DefaultWindow *>(gui->createWindow("AlfiskoSkin/Label", "", 0.300f, 0.05f, 0.10f, 0.1f));
  staticText->setText("[image='TaharezLook/Ear']");
  staticText = static_cast<CEGUI::DefaultWindow *>(gui->createWindow("AlfiskoSkin/Label", "", 0.60f, 0.05f, 0.10f, 0.1f));
  staticText->setText("[image='TaharezLook/Man']");
  return std::string("DisplaySound");
}

void		DisplaySound::launch()
{
  Menu					*menu = Menu::getMenu(NULL);
  Gui					*gui = Gui::getGui(NULL);
  std::vector<IModule *>		tmp;

  gui->init();
  tmp.push_back(new Back(menu->getMods()));
  menu->changeMods(tmp);
  gui->add_buttons(menu->getMods(), 0.2);
}
