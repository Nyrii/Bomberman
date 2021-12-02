//
// ListScores.cpp for indie studio in /home/arino_a/Documents/cpp_indie_studio
//
// Made by Aurelien Arino
// Login   <arino_a@epitech.net>
//
// Started on  Thu Apr 28 10:12:05 2016 Aurelien Arino
// Last update Mon May  9 18:19:44 2016 Alban Combaud
//

#include <fstream>
#include "ListScores.hh"

void ListScores::addScore(const Score &src) {
  std::ofstream fs;

  fs.open(".highscores.txt", std::ofstream::out | std::ofstream::trunc);
  _highscores.push_back(src);
  sort();
  for (std::vector<Score>::iterator it = _highscores.begin(); it != _highscores.end(); it++)
    fs << it->getPseudo() << " " << it->getScore() << std::endl;
  fs.close();
}

bool ListScores::fillListScore() {
  std::string str;
  std::ifstream fs(".highscores.txt");
  std::vector<Score>::iterator it = _highscores.begin();
  std::string s_tmp;

  if (fs.good()) {
    while (std::getline(fs, str)) {
      Score tmp;
      if ((s_tmp = tmp.fetchPseudo(str)) == "") {
	std::cout << "Error : Unable to get Pseudo nor Score in highscore file.";
	return false;
      }
      tmp.setPseudo(s_tmp);
      tmp.setScore(tmp.fetchScore(str));
      _highscores.push_back(tmp);
      str.clear();
      it++;
    }
  } else {
    std::cerr << "Error : Cannot read or access the highscore file." << std::endl;
    str = "";
  }
  fs.close();
  return true;
}

ListScores::ListScores() {}

ListScores::~ListScores() {}

ListScores::ListScores (const ListScores &src) {
  _highscores = src._highscores;
}

ListScores &ListScores::operator=(const ListScores &src) {
  if (this != &src) {
    _highscores = src._highscores;
  }
  return *this;
}

std::vector<Score> ListScores::getHighscores() const {
  return _highscores;
}

void ListScores::setHighscores(const std::vector<Score> &src) {
  _highscores = src;
}

void ListScores::sort() {
  Score hold;

  for (std::vector<Score>::iterator it = _highscores.begin(); it != _highscores.end(); it++) {
    for (unsigned int i = 0; i < _highscores.size() - 1; i++) {
      if (_highscores.at(i).getScore() < _highscores.at(i + 1).getScore()) {
	hold = _highscores.at(i);
	_highscores.at(i) = _highscores.at(i + 1);
	_highscores.at(i + 1) = hold;
      }
    }
  }
  int len = _highscores.size();
  std::vector<Score>::iterator it = _highscores.end();
  while (len > 10) {
    _highscores.erase(it);
    it--;
    len--;
  }
}
