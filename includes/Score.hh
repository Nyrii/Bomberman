//
// Score.hh for indie studio in /home/arino_a/Documents/cpp_indie_studio
//
// Made by Aurelien Arino
// Login   <arino_a@epitech.net>
//
// Started on  Wed Apr 27 10:58:51 2016 Aurelien Arino
// Last update Sun Jun  5 22:00:49 2016 Aurelien Arino
//

#ifndef SCORE_HH_
# define SCORE_HH_

# include <iostream>

class Score{
public:
  // CTOR DTOR
  Score();
  ~Score();
  Score(const Score &);
  Score &operator=(const Score &);

  // GETTERS
  std::string getPseudo() const;
  int getScore() const;

  // SETTERS
  void setPseudo(const std::string &);
  void setScore(const int &);

  // METHODS
  std::string cut(const std::string &);
  int cutNb(const std::string &);
  std::string trim(const std::string &) const ;
  std::string fetchPseudo(const std::string &);
  int fetchScore(const std::string &);

private:
  std::string _pseudo;
  int _score;
};

#endif /* !SCORES_HH_ */
