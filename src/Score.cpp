//
// Score.cpp for indie studio in /home/arino_a/Documents/cpp_indie_studio
//
// Made by Aurelien Arino
// Login   <arino_a@epitech.net>
//
// Started on  Wed Apr 27 10:58:59 2016 Aurelien Arino
// Last update Sun Jun  5 22:00:36 2016 Aurelien Arino
//

#include <cstdlib>
#include <algorithm>
#include "Score.hh"

Score::Score() {}

std::string Score::trim(const std::string &str) const {
  std::string tmp = str;

  tmp.erase(std::remove(tmp.begin(), tmp.end(), ';'), tmp.end());
  size_t end = tmp.find_last_not_of(" \t");
  size_t begin = tmp.find_first_not_of(" \t");
  if (std::string::npos != end)
    tmp = tmp.substr( 0, end + 1);
  if (std::string::npos != begin)
    tmp = tmp.substr(begin);
  if (tmp.find_first_not_of(' ') == std::string::npos)
    tmp.clear();
  return tmp;
}

std::string Score::fetchPseudo(const std::string &str) {
  std::string tmp = trim(str);
  std::string ret = "";
  size_t i = 0;
  int count = 0;

  for (size_t i = 0; i < tmp.size(); i++) {
    if (tmp.at(i) == ' ')
      count++;
  }
  if (count == 0)
    return "";
  while (tmp.at(i) != ' ' && i < tmp.size()) {
    ret += tmp.at(i);
    i++;
  }
  return ret;
}

int Score::fetchScore(const std::string &str) {
  std::string tmp = trim(str);
  std::string nb;

  for (size_t i = _pseudo.size(); i < tmp.size(); i++)
    nb += tmp.at(i);
  return std::atoi(nb.c_str());
}

Score::~Score() {}

Score::Score(const Score &src) {
  _pseudo = src._pseudo;
  _score = src._score;
}

Score &Score::operator=(const Score &src) {
  if (this != &src) {
    _pseudo = src._pseudo;
    _score = src._score;
  }
  return *this;
}

void Score::setPseudo(const std::string &src) {
  _pseudo = src;
}


void Score::setScore(const int &src) {
  _score = src;
}

std::string Score::getPseudo() const {
  return _pseudo;
}


int Score::getScore() const {
  return _score;
}
