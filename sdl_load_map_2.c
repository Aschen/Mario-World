#include "epikong_sdl.h"

int		load_background(t_game *game)
{
  SDL_Rect	p;
  SDL_Surface	*background;
  SDL_Surface	*bg_image;
  int		width;
  int		height;

  width = game->size_tile * game->map->x;
  height = game->size_tile * game->map->y;
  p.x = 0;
  p.y = 0;
  if (!(background = SDL_CreateRGBSurface(SDL_HWSURFACE
					  , width, height, 32, 0, 0, 0, 0)))
    return (_error(strdup("load_background : CreateRGBSurface")));
  if ((bg_image = IMG_Load("images/background.bmp")) == NULL)
    return (_error(strdup("load_background : IMGLoad")));
  if (!(bg_image = rotozoomSurfaceXY(bg_image, 0.0,
				     (double)(width) / BACKGROUND_X,
				     (double)(height) / BACKGROUND_Y, 1)))
    return (_error(strdup("load_background : rotozoom")));
  if (SDL_BlitSurface(bg_image, NULL, background, &p) < 0)
    return (_error(strdup("load_background : BlitSurface")));
  game->background = background;
  SDL_FreeSurface(bg_image);
  return (0);
}
