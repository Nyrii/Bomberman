//
// MapError.hpp for MapError in /Users/noboud_n/Documents/Share/cpp_indie_studio/includes/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Wed Jun  1 13:17:48 2016 Nyrandone Noboud-Inpeng
// Last update Wed Jun  1 13:25:13 2016 Nyrandone Noboud-Inpeng
//

#ifndef MAPERROR_HPP_
# define MAPERROR_HPP_

# include "Error.hpp"

class		MapError : public Error
{
public:
  MapError(std::string const &message = "An error occured.") { _message = message; };
  virtual		~MapError() throw() {};
};

#endif /* !MAPERROR_HPP_ */
