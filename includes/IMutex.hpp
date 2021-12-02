//
// IMutex.hpp for Plazza in /home/wilmot_g/Rendu/cpp_plazza/TestHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed Apr  6 23:55:07 2016 guillaume wilmot
// Last update Fri May 27 02:10:11 2016 guillaume wilmot
//

#ifndef IMUTEX_HPP_
# define IMUTEX_HPP_

class IMutex {
public:
  virtual ~IMutex(void) {}
  virtual void lock(void) = 0;
  virtual void unlock(void) = 0;
  virtual bool trylock(void) = 0;
};

#endif /* !IMUTEX_HPP_ */
