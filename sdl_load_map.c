#include "epikong_sdl.h"

int		init_player(t_game *game, Uint32 x, Uint32 y)
{
  SDL_Rect	p;

  p.x = game->size_tile * x;
  p.y = game->size_tile * y;
  game->player.pos[X] = x;
  game->player.pos[Y] = y;
  game->player.sprites[PLEFT] = game->images[LPLAYER];
  game->player.sprites[PRIGHT] = game->images[RPLAYER];
  game->player.sprite = game->player.sprites[PLEFT];
  game->player.fall = 0;
  game->player.para = 0;
  game->player.jump = 0;
  game->player.direction_x = STOP;
  game->player.direction_y = STOP;
  if (SDL_BlitSurface(game->player.sprite, NULL, game->screen, &p) < 0)
    return (_error(strdup("init_player : BlitSurface")));
  return (0);
}

int		init_enemy(t_game *game, Uint32 x, Uint32 y, int nb)
{
  SDL_Rect	p;

  p.x = game->size_tile * x;
  p.y = game->size_tile * y;
  game->enemies[nb].pos[X] = x;
  game->enemies[nb].pos[Y] = y;
  game->enemies[nb].sprites[PLEFT] = game->images[LMOB];
  game->enemies[nb].sprites[PRIGHT] = game->images[RMOB];
  game->enemies[nb].sprite = game->enemies[nb].sprites[PLEFT];
  game->enemies[nb].direction = (nb % 2) ? LEFT : RIGHT;
  if (SDL_BlitSurface(game->enemies[nb].sprite, NULL, game->screen, &p) < 0)
    return (_error(strdup("init_enemy : BlitSurface")));
  return (0);
}

int		init_sprites(t_game *game)
{
  t_tile	tile;
  Uint32	x;
  Uint32	y;
  int		nb_en;

  nb_en = 0;
  game->map->enemies = 10;
  if ((game->enemies = malloc(game->map->enemies * sizeof(t_enemy))) == NULL)
    return (_error(strdup("init_sprites: Malloc fail\n")));
  memset(game->enemies, 0, game->map->enemies * sizeof(t_enemy));
  y = -1;
  while (++y < game->map->y)
    {
      x = -1;
      while (++x < game->map->x)
	{
	  tile = (int)((game->map)->data[y][x]);
	  if (tile == ENTER && init_player(game, x, y) < 0)
	    return (-1);
	  else if ((tile == LMOB || tile == RMOB) && init_enemy(game, x, y, nb_en++) < 0)
	    return (-1);
	}
    }
  return (0);
}

int		init_tiles(t_game *game)
{
  SDL_Surface	*tmp;
  t_tile	tile;
  SDL_Rect	p;
  Uint32	x;
  Uint32	y;

  y = -1;
  while (++y < game->map->y)
    {
      x = -1;
      while (++x < game->map->x)
	{
	  p.x = game->size_tile * x;
	  p.y = game->size_tile * y;
	  tile = (int)((game->map)->data[y][x]);
	  if (tile != LMOB && tile != RMOB && tile != ENTER)
	    {
	      tmp = game->images[tile];
	      if (SDL_BlitSurface(tmp, NULL, game->background, &p) < 0)
		return (_error(strdup("init_tiles : BlitSurface")));
	    }
	}
    }
  return (0);
}

int		init_map(t_game *game)
{
  SDL_Rect	p;

  p.x = 0;
  p.y = 0;
  game->map = game->maps_list[game->current];
  if (load_background(game) == -1)
    return (-1);
  if (init_tiles(game) < 0)
    return (-1);
  if (SDL_BlitSurface(game->background, NULL, game->screen, &p) < 0)
    return (_error(strdup("init_map : BlitSurface")));
  if (init_sprites(game) < 0)
    return (-1);
  SDL_Flip(game->screen);
  return (0);
}
