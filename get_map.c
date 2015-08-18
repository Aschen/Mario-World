/*
** get_map.c for epikong in /home/blanch_d/T2Rush1/etape_1
**
** Made by BLANCHARD
** Login   <blanch_d@epitech.net>
**
** Started on  Sat Mar  8 01:32:05 2014 BLANCHARD
** Last update Sun Mar  9 11:29:54 2014 Jeqn-Yves Bateman
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "epikong.h"

/*********************/
/*   CHANGE MAP      */
/*********************/
void		modif_map(t_map *info)
{
  Uint32	x;
  Uint32	y;
  int		o;

  y = 0;
  while (info->data[y] != NULL)
    {
      x = 0;
      while (x != info->x)
      	{
      	  o = 0;
      	  while (info->obj[o] != 0 && info->obj[o] != info->data[y][x])
	    o++;
      	  info->data[y][x] = o;
      	  info->c_map[y][x] = 0;
      	  x++;
      	}
      y++;
    }
}

/*********************/
/*FILL MAP WITH OBJS */
/*********************/
void		fill_map(t_map *info, FILE *fd)
{
  Uint32	y;
  Uint32	x;
  int		c;

  y = 0;
  rewind(fd);
  c = fgetc(fd);
  while (info->data[y] != NULL)
    {
      x = 0;
      while (x != info->x)
	{
	  if (c != '\n' && c != EOF)
	    {
	      info->data[y][x] = c;
	      c = fgetc(fd);
	    }
	  else
	    info->data[y][x] = 0;
	  x++;
	}
      c = fgetc(fd);
      y++;
    }
  modif_map(info);
}

/*********************/
/* STORE MAP DATA    */
/*********************/
int		store_map(Uint32 size, Uint32 line, t_map *info, FILE *fd)
{
  Uint32	i;

  i = 0;
  if ((info->data = malloc(sizeof(char *) * (info->x + 1))) == NULL ||
      (info->c_map = malloc(sizeof(int *) * (line + 1))) == NULL)
    {
      write(2, "Malloc Failed.\n", 15);
      return (-1);
    }
  while (i != line)
    if ((info->data[i] = malloc(sizeof(char) * (size + 1))) == NULL ||
	(info->c_map[i++] = malloc(sizeof(int) * (size + 1))) == NULL)
      {
	write(2, "Malloc Failed.\n", 15);
	return (-1);
      }
  info->data[i] = NULL;
  info->c_map[i] = NULL;
  fill_map(info, fd);
  return (1);
}

/*********************/
/* GET INFO OF MAP  */
/*********************/
int		get_info(char *map, t_map *info)
{
  FILE		*fd;
  int		c;
  Uint32	len;

  len = 0;
  c = 0;
  init_strt(info);
  if ((fd = fopen(map, "r")) == NULL)
    return (-1);
  while (c != EOF && (c = fgetc(fd)) != EOF)
    {
      if (c == '\n' && (c = fgetc(fd)) != EOF)
	{
	  if (len > info->x)
	    info->x = len;
	  info->y++;
	  len = 0;
	}
      else
	len++;
    }
  if (store_map(info->x, info->y, info, fd) == -1)
    return (-1);
  //fclose(fd);
  return (1);
}

void		init_strt(t_map *info)
{
  info->x = 1;
  info->y = 1;
  info->obj[0] = '.';
  info->obj[1] = 'w';
  info->obj[2] = 's';
  info->obj[3] = 'm';
  info->obj[4] = 'o';
  info->obj[5] = 'i';
  info->obj[6] = 'k';
  info->obj[7] = 0;
}
