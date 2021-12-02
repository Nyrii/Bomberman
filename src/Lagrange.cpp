//
// Lagrange.cpp for Lagrange in /Users/noboud_n/Documents/Share/cpp_indie_studio/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Mon May 30 21:04:37 2016 Nyrandone Noboud-Inpeng
// Last update Sun Jun  5 21:51:04 2016 Nyrandone Noboud-Inpeng
//

#include "Lagrange.hh"

Lagrange::Lagrange()
{

}

Lagrange::~Lagrange()
{

}

float		Lagrange::lagrange(int currentDistance, int distanceMax, int weightMax) const
{
  float		temp;
  float		total;
  int		x[2];
  int		y[2];
  int		len;
  int		i;
  int		j;

  x[0] = 0;
  y[0] = 0;
  x[1] = distanceMax;
  y[1] = weightMax;
  len = 2;
  total = 0.0;
  for (i = 0; i < len; i++)
    {
      temp = 1;
      for(j = 0; j < len; j++)
	{
	  if (j != i)
	    temp = temp * (currentDistance - x[j]) / (x[i] - x[j]);
	}
      temp *= y[i];
      total += temp;
    }
  return (total);
}
