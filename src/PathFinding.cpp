//
// PathFinding.cpp for PathFinding in /Users/noboud_n/rendu/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Thu Apr 28 10:31:25 2016 Nyrandone Noboud-Inpeng
// Last update Sat Jun  4 18:15:57 2016 guillaume wilmot
//

#include <vector>
#include "PathFinding.hh"

PathFinding::PathFinding()
{
  _nbPaths = 0;
  _posX = 0;
  _posY = 0;
}

PathFinding::~PathFinding() {}

void			PathFinding::setListOnQueue(t_paths **paths, int id) const
{
  t_paths		*tmp;

  tmp = (*paths)->next;
  while (tmp->id != id && tmp != *paths)
    tmp = tmp->next;
  if (tmp->id == id)
    *paths = tmp;
}

float			PathFinding::extractPath(int key, std::vector<int> *queue,
						 t_paths *end, t_paths *start) const
{
  float			len;

  delete queue;
  if (key == 0)
    return (-1);
  for (len = 1; end->id != start->id; len++)
    setListOnQueue(&end, end->visited_by);
  return (len);
}

void			PathFinding::reinitPaths(t_paths *paths) const
{
  t_paths		*tmp;

  tmp = paths;
  while (tmp->next != paths)
    {
      tmp->visited = 0;
      tmp = tmp->next;
    }
  tmp->visited = 0;
}

float			PathFinding::pathfinding(t_paths *path, int y, int x) const
{
  t_paths		*start;
  int			end;
  int			i;
  std::vector<int>	*queue;

  end = 0;
  start = path;
  queue = new std::vector<int>;
  queue->push_back(path->id);
  reinitPaths(path);
  path->visited = 1;
  path->visited_by = path->id;
  while (queue->size() > 0 && !end)
    {
      setListOnQueue(&path, queue->at(0));
      queue->erase(queue->begin());
      for (i = 0; i < 4 && !end; i++)
	if (path->neighbours[i])
	  if (!(path->neighbours[i])->visited)
	    {
	      queue->push_back((path->neighbours[i])->id);
	      (path->neighbours[i])->visited = 1;
	      (path->neighbours[i])->visited_by = path->id;
	      if ((path->neighbours[i])->pos[0] == y && (path->neighbours[i])->pos[1] == x)
		end = 1;
	    }
    }
  return (extractPath(end, queue, path, start));
}

int			PathFinding::getBestWay(t_paths *path, t_infos &infos) const
{
  float			bestLen;
  float			len;
  int			bestWay;
  int			i;
  int			k;

  bestLen = 0;
  bestWay = 9;
  k = 0;
  for (i = 0; i < 4; i++)
    if (path->neighbours[i])
      {
	if ((path->neighbours[i])->pos[0] == infos.y && (path->neighbours[i])->pos[1] == infos.x)
	  {
	    bestLen = 1;
	    bestWay = i;
	    i = 4;
	  }
	else if (k == 0)
	  {
	    bestLen = pathfinding(path->neighbours[i], infos.y, infos.x);
	    if (bestLen != -1)
	      {
		k++;
		bestWay = i;
	      }
	  }
	else if ((len = pathfinding(path->neighbours[i], infos.y, infos.x)) < bestLen && len != -1)
	  {
	    bestLen = len;
	    bestWay = i;
	  }
      }
  infos.distance = bestLen;
  return (bestWay);
}

int			PathFinding::findBestWay(int x, int y, t_infos &infos) const
{
  t_paths		*tmp;
  int			end;

  tmp = _paths->next;
  end = 0;
  while (tmp != _paths && !end)
    {
      if (tmp->pos[0] != y || tmp->pos[1] != x)
	tmp = tmp->next;
      else
	end = 1;
    }
  if (tmp->pos[0] == y && tmp->pos[1] == x)
    {
      end = getBestWay(tmp, infos);
      if (end == 0 || end == 1)
	return (end == 0 ? UP : RIGHT);
      else if (end == 2 || end == 3)
	return (end == 2 ? DOWN : LEFT);
    }
  return (-1);
}

int			PathFinding::isBlocked(int i, int j, Map &map, Players &players) const
{
  if (i < 0 || j < 0)
    return (1);
  if (i >= map.getMaxY() || j >= map.getMaxX())
    return (1);
  if ((!map.isAnObstacle(j, i, players)) || (_posX == j && _posY == i))
    return (0);
  return (1);
}

void			PathFinding::addNeighbour(t_paths **paths, int i, int j, int k) const
{
  t_paths		*tmp;

  if ((tmp = (*paths)->next) == NULL)
    return;
  while (tmp != *paths && (tmp->pos[0] != i || tmp->pos[1] != j))
    tmp = tmp->next;
  if (tmp->pos[0] == i && tmp->pos[1] == j)
    (*paths)->neighbours[k] = tmp;
}

void			PathFinding::addNeighbours(t_paths **paths, Map &map,
						   Players &players) const
{
  int			tiles[4][2];
  int			i;

  tiles[0][0] = (*paths)->pos[0] - 1;
  tiles[1][0] = (*paths)->pos[0];
  tiles[2][0] = (*paths)->pos[0] + 1;
  tiles[3][0] = (*paths)->pos[0];
  tiles[0][1] = (*paths)->pos[1];
  tiles[1][1] = (*paths)->pos[1] + 1;
  tiles[2][1] = (*paths)->pos[1];
  tiles[3][1] = (*paths)->pos[1] - 1;
  for (i = 0; i < 4; i++)
    {
      if (!isBlocked(tiles[i][0], tiles[i][1], map, players))
	addNeighbour(paths, tiles[i][0], tiles[i][1], i);
    }
}

void			PathFinding::addInPaths(t_paths **paths, int i, int j, int id) const
{
  t_paths		*elem;
  t_paths		*tmp;
  int			k;

  elem = new t_paths;
  elem->visited = 0;
  elem->id = id;
  elem->pos[0] = i;
  elem->pos[1] = j;
  elem->next = elem;
  for (k = 0; k < 4; k++)
    elem->neighbours[k] = NULL;
  if (*paths != NULL)
    {
      tmp = *paths;
      while (tmp->next != *paths)
	tmp = tmp->next;
      elem->next = *paths;
      tmp->next = elem;
    }
  else
    *paths = elem;
}

void			PathFinding::freePaths()
{
  t_paths	*tmp;
  t_paths	*tmp2;

  tmp = _paths->next;
  while (tmp != _paths)
    {
      tmp2 = tmp;
      tmp = tmp->next;
      delete tmp2;
    }
  delete tmp;

}

void			PathFinding::processPaths(Map &map, int const x,
						  int const y, Players &players)
{
  t_paths		*tmp;
  int			i;
  int			j;
  int			id;

  _posX = x;
  _posY = y;
  _paths = NULL;
  _nbPaths = 0;
  id = 1;
  for (i = 0; i < map.getMaxY(); i++)
    for (j = 0; j < map.getMaxX(); j++)
      if (map.getMap()[i][j]->getItem() != BORDER)
	{
	  addInPaths(&_paths, i, j, id++);
	  _nbPaths++;
	}
  if (_paths == NULL)
    return ;
  tmp = _paths->next;
  while (tmp != _paths)
    {
      addNeighbours(&tmp, map, players);
      tmp = tmp->next;
    }
  addNeighbours(&_paths, map, players);
}
