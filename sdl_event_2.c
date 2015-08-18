#include "epikong_sdl.h"

int		key_escape(SDL_Event *event, t_game *game)
{
  if (event->type ==SDL_KEYDOWN)
    {
      if (game->current == MENU)
	game->flag = QUIT;
      else
	game->current = MENU;
      return (SDLK_ESCAPE);
    }
  return (0);
}

int		key_space(SDL_Event *event, t_game *game)
{
  if (event->type == SDL_KEYDOWN)
    {
      if (game->player.fall)
	{
	  game->player.para = ((game->player.para) ? 0 : 1);
	}
      else if (game->player.jump == 0)
	{
	  game->player.jump = 2;
	  if (game->player.direction_x == RIGHT)
	    game->player.jump = 12;
	  if (game->player.direction_x == LEFT)
	    game->player.jump = 22;
	}
    }
  return (1);
}

int		key_right(SDL_Event *event, t_game *game)
{
  if (event->type == SDL_KEYDOWN)
    {
      game->player.direction_x = RIGHT;
      game->player.sprite = game->player.sprites[PRIGHT];
    }
  else
      game->player.direction_x = STOP;
  return (1);
}

int		key_left(SDL_Event *event, t_game *game)
{
  if (event->type == SDL_KEYDOWN)
    {
      game->player.direction_x = LEFT;
      game->player.sprite = game->player.sprites[PLEFT];
    }
  else
    game->player.direction_x = STOP;
  return (1);
}

int		key_up(SDL_Event *event, t_game *game)
{
  if (event->type == SDL_KEYDOWN)
      game->player.direction_y = UP;
  else
      game->player.direction_y = STOP;
  return (1);
}

