//
// StopSleep.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sat May 28 20:14:26 2016 guillaume wilmot
// Last update Tue May 31 03:48:20 2016 guillaume wilmot
//

#ifndef STOPSLEEP_HPP_
# define STOPSLEEP_HPP_

# include <iostream>
# include <unistd.h>
# include <chrono>
# include <stdexcept>
# include "ProtectedVar.hpp"

class		StoppableTimer {
public:
  StoppableTimer(float time, ProtectedVar<bool> *end)
  {
    std::chrono::high_resolution_clock::time_point init = std::chrono::high_resolution_clock::now();

    while (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() < std::chrono::duration_cast<std::chrono::microseconds>(init.time_since_epoch()).count() + static_cast<long>(time * 1000000))
      {
	if (end->get())
	  throw std::exception();
	usleep(100);
      }
  }
};

#endif /* !_STOPSLEEP_HPP_ */
