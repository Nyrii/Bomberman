//
// SkinManager.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 15 05:54:01 2016 guillaume wilmot
// Last update Sun May 15 05:58:59 2016 guillaume wilmot
//

#ifndef SKINMANAGER_HPP_
# define SKINMANAGER_HPP_

# include "irrlicht.h"

class		SkinManager {
public:
  SkinManager();
  ~Skinanager();

  int			generate();
  int			cleanup();
private:
  Skin			_skin;
};

#endif /* !SKINMANAGER */
