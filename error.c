/*
** error.c for error in /home/batema_j/rendu/T2Rush1/etape_1
**
** Made by Jeqn-Yves Bateman
** Login   <batema_j@epitech.net>
**
** Started on  Sat Mar  8 08:38:49 2014 Jeqn-Yves Bateman
** Last update Sun Mar  9 16:46:17 2014 BLANCHARD
*/

#include "epikong.h"

void		check_map_play(t_map *info, Uint32 x, Uint32 y)
{
  if ((x + 1) <= info->x && info->c_map[y][x + 1] == 1)
    {
      info->c_map[y][x + 1] = 2;
      check_map_play(info, (x + 1), y);
    }
  if (info->c_map[y][x - 1] == 1)
    {
      info->c_map[y][x - 1] = 2;
      check_map_play(info, (x - 1), y);
    }
  if ((y + 1) <= info->y && info->c_map[y + 1][x] == 1)
    {
      info->c_map[y + 1][x] = 2;
      check_map_play(info, x, (y + 1));
    }
  if (info->c_map[y - 1][x] == 1)
    {
      info->c_map[y - 1][x] = 2;
      check_map_play(info, x, (y - 1));
    }
}

void		get_pos(t_map *info)
{
  Uint32	x;
  Uint32	y;

  y = 0;
  while (info->data[y] != NULL)
    {
      x = 0;
      while (x != info->x)
	{
	  if (info->data[y][x] == 5)
	    {
	      check_map_play(info, x, y);
	      return ;
	    }
	  x++;
	}
      y++;
    }
}


void		set_paths(t_map *info)
{
  Uint32	x;
  Uint32	y;

  y = 0;
  while (info->data[y] != NULL)
    {
      x = 0;
      while (x != info->x)
	{
	  if ((y + 1) <= info->y &&
	      (info->data[y + 1][x] == 1 || info->data[y + 1][x] == 2)
	      && info->data[y][x] != 1)
	    info->c_map[y][x] = 1;
	  //if (y > 1 && info->data[y + 1] != NULL)
	  //set_jump(info, x, y);
	  if (info->data[y][x] == 2)
	    {
	      printf("%d, %d\n", y, x);
	      info->c_map[y][x] = 1;
	    }
	  x++;
	}
      y++;
    }
  get_pos(info);
}
