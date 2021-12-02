//
// MeshError.hpp for MeshError in /Users/noboud_n/Documents/Share/cpp_indie_studio/includes/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Wed Jun  1 13:17:24 2016 Nyrandone Noboud-Inpeng
// Last update Wed Jun  1 13:29:59 2016 Nyrandone Noboud-Inpeng
//

#ifndef MESHERROR_HPP_
# define MESHERROR_HPP_

# include "Error.hpp"

class		MeshError : public Error
{
public:
  MeshError(std::string const &message = "An error occured.") { _message = message; };
  virtual		~MeshError() throw() {};
};

#endif /* !MESHERROR_HPP_ */
