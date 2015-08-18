/*
** check_map.c for check_map in /home/batema_j/rendu/T2Rush1/etape_1
** 
** Made by Jeqn-Yves Bateman
** Login   <batema_j@epitech.net>
** 
** Started on  Sat Mar  8 21:16:08 2014 Jeqn-Yves Bateman
** Last update Sun Mar  9 21:08:23 2014 Jeqn-Yves Bateman
*/

#include <unistd.h>
#include "epikong.h"

void		check_obj(int c)
{
  if (c != '\n' && c != EOF && c != 'w' && c != 'k' && c != 's' && c != 'i' &&
      c != 'm' && c != '.' && c != 'o')
    {
      write(2, "Invalid map\n", 12);
      exit(-1);
    }
}

void		check_map_objs(t_map *info)
{
  Uint32	x;
  Uint32	y;
  int		check[3];

  y = 0;
  while (info->data[y] != NULL)
    {
      x = 0;
      while (x != info->x)
	{
	  (info->data[y][x] == 4 || check[0] == 1)
	    ? (check[0] = 1) : (check[0] = 0);
	  (info->data[y][x] == 5 || check[1] == 1) 
	    ? (check[1] = 1) : (check[1] = 0);
	  (info->data[y][x] == 6 || check[2] == 1)
	    ? (check[2] = 1) : (check[2] = 0);
	  x++;
	}
      y++;
    }
  if (check[0] != 1 || check[1] != 1 || check[2] != 1)
    {
      write(2, "Map is missing objects.\n", 24);
      exit (-1);
    }
}

int		check_square(Uint32 y, Uint32 x, t_map *info)
{
  if ((y == 0 || (y + 1) == info->y) &&
      (info->data[y][x] != 1 && info->data[y][x] != 7))
    return (1);
  if (x == 0 && info->data[y][x] != 1)
    return (1);
  if (x == info->x  && info->data[y][x] != 1)
    return (1);
  return (0);
}

void		check_wall(t_map *info)
{
  Uint32	x;
  Uint32	y;
  int		check;

  y = 0;
  check = 0;
  while (info->data[y] != NULL)
    {
      x = 0;
      while (x != info->x)
	{
	  check = check_square(y, x, info);
	  if (check == 1)
	    {
	      write(2, "Invalid Map\n", 12);
	      exit(-1);
	    }
	  x++;
	}
      y++;
    }
}
