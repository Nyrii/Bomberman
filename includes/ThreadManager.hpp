//
// ThreadManager.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun May 29 02:58:48 2016 guillaume wilmot
// Last update Mon May 30 16:33:12 2016 guillaume wilmot
//

#ifndef THREADMANAGER_HPP_
# define THREADMANAGER_HPP_

# include <thread>
# include <vector>
# include "ProtectedVar.hpp"

class		ThreadManager {
public:
  static ThreadManager	&get() {static ThreadManager _mgr; return (_mgr);}

  void			addThread(std::thread *);
  void			end();

private:

  ThreadManager() {};
  ThreadManager(const ThreadManager &);

  void			operator=(const ThreadManager &);

  ProtectedVar<std::vector<std::thread *> >	_threads;
};

#endif /* !THREAD_MANAGER */
