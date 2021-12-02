//
// PathFinding.hh for PathFinding in /Users/noboud_n/rendu/cpp_indie_studio/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Thu Apr 28 10:33:37 2016 Nyrandone Noboud-Inpeng
// Last update Mon May 30 22:09:04 2016 guillaume wilmot
//

#ifndef PATHFINDING_HH_
# define PATHFINDING_HH_

# include "Map.hh"
# include "IA.hh"

typedef struct          s_paths
{
  int			id;
  int			visited;
  int			visited_by;
  int			pos[2];
  int			best_way[2];
  struct s_paths	*neighbours[4];
  struct s_paths	*next;
}			t_paths;

class		PathFinding
{
public:
  PathFinding();
  ~PathFinding();
  void		setListOnQueue(t_paths **, int) const;
  float		extractPath(int, std::vector<int> *, t_paths *, t_paths *) const;
  void		reinitPaths(t_paths *) const;
  float		pathfinding(t_paths *, int, int) const;
  int		getBestWay(t_paths *, t_infos &) const;
  int		findBestWay(int, int, t_infos &) const;
  int		isBlocked(int, int, Map &, Players &) const;
  void		addNeighbour(t_paths **, int, int, int) const;
  void		addNeighbours(t_paths **, Map &, Players &) const;
  void		addInPaths(t_paths **, int, int, int) const;
  void		freePaths();
  void		processPaths(Map &, int const , int const, Players &);
private:
  t_paths	*_paths;
  int		_nbPaths;
  int		_posX;
  int		_posY;
};

#endif /* !PATHFINDING_HH_ */
