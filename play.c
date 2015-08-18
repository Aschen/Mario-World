/*
** play.c for epikong in /home/blanch_d/T2Rush1/etape_2
**
** Made by BLANCHARD
** Login   <blanch_d@epitech.net>
**
** Started on  Sat Mar  8 20:34:42 2014 BLANCHARD
** Last update Sun Mar  9 16:46:34 2014 BLANCHARD
*/

#include "epikong_sdl.h"

void		move_enemies(t_game *game)
{
  int		i;
  int		x;
  int		y;
  t_tile	in;
  t_tile	down;
  SDL_Surface	*tmp;

  i = 0;
  while (game->enemies[i].sprite != NULL)
    {
      if (game->enemies[i].pos[X] % 2)
	tmp = game->enemies[i].sprites[PLEFT];
      else
	tmp = game->enemies[i].sprites[PRIGHT];
      game->enemies[i].sprite = tmp;
      x = game->enemies[i].pos[X];
      x += ((game->enemies[i].direction == RIGHT) ? 1 : -1);
      y = game->enemies[i].pos[Y];
      in = game->map->data[y][x];
      down = game->map->data[y + 1][x];
      if (in == WALL || down == EMPTY)
	game->enemies[i].direction = -game->enemies[i].direction;
      game->enemies[i].pos[X] += game->enemies[i].direction;
      i++;
    }
}

void		move_all(t_game *game)
{
  move_enemies(game);
  move_player(game);
}

int		hook_position(t_game *game)
{
  int		pos[2];

  pos[X] = game->player.pos[X];
  pos[Y] = game->player.pos[Y];
  if (game->current == MENU)
    if (pos[Y] == 15 && !(pos[X] % 5))
      {
	game->current = pos[X] / 5;
	return (1);
      }
  if (game->current > MENU)
    {
      if (game->map->data[pos[Y]][pos[X]] == EXIT)
	{
	  if (game->maps_list[game->current + 1] !=  NULL)
	      game->current++;
	  else
	      game->current = 0;
	  return (1);
	}
    }
  return (0);
}

int		play(t_game *game)
{
  int		flag;
  int		cs;
  SDL_Event	event;

  flag = CONTINUE;
  cs = 0;
  while (flag == CONTINUE)
    {
      if (cs % 30 == 0)
	{
	  cs = 0;
	  move_all(game);
	}
      if (SDL_PollEvent(&event))
	flag = hook_event(&event, game);
      refresh_sprites(game);
      if (hook_position(game))
	flag = QUIT;
      cs++;
    }
  sleep(1);
  return (1);
}
