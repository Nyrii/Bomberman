//
// GameError.hpp for GameError in /Users/noboud_n/Documents/Share/cpp_indie_studio/includes/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Wed Jun  1 13:15:44 2016 Nyrandone Noboud-Inpeng
// Last update Wed Jun  1 13:25:27 2016 Nyrandone Noboud-Inpeng
//

#ifndef GAMEERROR_HPP_
# define GAMEERROR_HPP_

# include "Error.hpp"

class		GameError : public Error
{
public:
  GameError(std::string const &message = "An error occured.") { _message = message; };
  virtual		~GameError() throw() {};
};

#endif /* !GAMEERROR_HPP_ */
