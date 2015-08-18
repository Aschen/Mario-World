/*
** sdl.c for epikong in /home/blanch_d/T2Rush1/etape_1
**
** Made by BLANCHARD
** Login   <blanch_d@epitech.net>
**
** Started on  Sat Mar  8 16:26:22 2014 BLANCHARD
** Last update Sun Mar  9 16:40:43 2014 BLANCHARD
*/

#include "epikong_sdl.h"

int		load_images(t_game *game)
{
  char		*files[NB_IMAGES] = {"images/empty.png",
				     "images/wall.bmp",
				     "images/ladder.png",
				     "images/lgoomba.png",
				     "images/exit.png",
				     "images/empty.png",
				     "images/key.png",
				     "images/lplayer.png",
				     "images/rplayer.png",
				     "images/rgoomba.png"};
  int		i;
  double	r;

  game->images[0] = NULL;
  i = 0;
  r = (double)(game->size_tile) / SIZE_IMAGE;
  while (i < NB_IMAGES)
    {
      if ((game->images[i] = IMG_Load(files[i])) == NULL)
	return (_error(strdup("load_images : ImgLoad")));
      if (!(game->images[i] = rotozoomSurfaceXY(game->images[i], 0.0, r, r, 1)))
	return (_error(strdup("load_images : rotozoom")));
      i++;
    }
  return (0);
}

int		init_base(t_game *game)
{
  int		width;
  int		height;

  width = game->size_tile * game->map->x;
  height = game->size_tile * game->map->y;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return (_error(strdup("init_base : Init")));
  if (!(game->screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE)))
    return (_error(strdup("init_base : SetVideoMode")));
  SDL_WM_SetCaption("Epikong", NULL);
  return (0);
}

int		get_size_tile(int size_x_map, int size_y_map)
{
  int		size_tile;

  size_tile = MAX_HEIGHT / size_y_map;
  if (MAX_WIDTH / size_x_map < size_tile)
    size_tile = MAX_WIDTH / size_x_map;
  return (size_tile);
}

int		load_maps(t_game *game, int nb_map, char **maps)
{
  int		i;
  int		j;

  if ((game->maps_list = malloc(sizeof(t_map*) * (nb_map + 2))) == NULL)
    return (_error(strdup("load_maps : malloc")));
  j = 0;
  while (j < (nb_map + 2))
    if ((game->maps_list[j++] = malloc(sizeof(t_map))) == NULL)
      return (_error(strdup("load_maps : malloc")));
  game->maps_list[nb_map + 1] = NULL;
  if (get_info("maps/menu", game->maps_list[MENU]) < 0)
    return (-1);
  j = 1;
  i = 0;
  while (i < nb_map)
    {
      if (get_info(maps[i++], game->maps_list[j++]) < 0)
	return (-1);
    }
  game->map = game->maps_list[MENU];
  game->current = MENU;
  game->size_tile = get_size_tile(game->map->x, game->map->y);
  return (0);
}

int		init_game(t_game *game, int nb_map, char **maps)
{
  game->map = NULL;
  game->maps_list = NULL;
  game->screen = NULL;
  game->images[0] = NULL;
  game->background = NULL;
  game->enemies = NULL;
  if (load_maps(game, nb_map, maps) == -1)
    return (-1);
  if (init_base(game) == -1)
    return (-1);
  if (load_images(game) < 0)
    return (-1);
  return (0);
}
