//
// ListScores.hh for indie studio in /home/arino_a/Documents/cpp_indie_studio
//
// Made by Aurelien Arino
// Login   <arino_a@epitech.net>
//
// Started on  Thu Apr 28 10:10:52 2016 Aurelien Arino
// Last update Sun Jun  5 21:51:31 2016 Nyrandone Noboud-Inpeng
//

#ifndef LISTSCORES_HH_
# define LISTSCORES_HH_

# include <iostream>
# include <vector>
# include "Score.hh"

class ListScores{
public:
  ListScores();
  ~ListScores();
  ListScores(const ListScores &);
  ListScores &operator=(const ListScores &);

  std::vector<Score> getHighscores() const;

  void setHighscores(const std::vector<Score> &);

  void sort();
  bool fillListScore();
  void addScore(const Score &);
private:
  std::vector<Score> _highscores;
};

#endif /* !LISTSCORES_HH_ */
