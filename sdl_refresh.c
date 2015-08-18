#include "epikong_sdl.h"

int		refresh_enemies(t_game *game)
{
  SDL_Rect	p;
  int		i;

  i = 0;
  while (game->enemies[i].sprite != NULL)
    {
      p.x = game->enemies[i].pos[X] * game->size_tile;
      p.y = game->enemies[i].pos[Y] * game->size_tile;
      if (SDL_BlitSurface(game->enemies[i].sprite, NULL, game->screen, &p) < 0)
	return (_error(strdup("refresh_enemies : BlitSurface")));
      i++;
    }
  return (0);
}

int		refresh_player(t_game *game)
{
  SDL_Rect	p;

  p.x = game->player.pos[X] * game->size_tile;
  p.y = game->player.pos[Y] * game->size_tile;
  if (SDL_BlitSurface(game->player.sprite, NULL, game->screen, &p) < 0)
    return (_error(strdup("refresh_player : BlitSurface")));
  return (0);
}

int		refresh_sprites(t_game *game)
{
  SDL_Rect	p;

  p.x = 0;
  p.y = 0;
  if (SDL_BlitSurface(game->background, NULL, game->screen, &p) < 0)
    return (_error(strdup("refresh_sprites : BlitSurface")));
  if (refresh_player(game) < 0)
    return (-1);
  if (refresh_enemies(game) < 0)
    return (-1);
  SDL_Flip(game->screen);
  return (0);
}
