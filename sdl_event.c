#include "epikong_sdl.h"

int			key_down(SDL_Event *event, t_game *game)
{
  if (event->type == SDL_KEYDOWN)
      game->player.direction_y = DOWN;
  else
      game->player.direction_y = STOP;
  return (1);
}

void			get_event(t_event_handler key_event[EVENTS])
{
  key_event[0].key_code = SDLK_DOWN;
  key_event[0].fptr = &key_down;
  key_event[1].key_code = SDLK_UP;
  key_event[1].fptr = &key_up;
  key_event[2].key_code = SDLK_LEFT;
  key_event[2].fptr = &key_left;
  key_event[3].key_code = SDLK_RIGHT;
  key_event[3].fptr = &key_right;
  key_event[4].key_code = SDLK_ESCAPE;
  key_event[4].fptr = &key_escape;
  key_event[5].key_code = SDLK_SPACE;
  key_event[5].fptr = &key_space;
  key_event[6].fptr = NULL;
}

int			hook_event(SDL_Event *event, t_game *game)
{
  t_event_handler	key_event[EVENTS];
  int			ret;
  Uint32		i;

  i = 0;
  ret = CONTINUE;
  get_event(key_event);
  if (event->type == SDL_QUIT)
    ret = 0;
  else if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
    while (key_event[i].fptr)
      {
	if (key_event[i].key_code == event->key.keysym.sym)
	  ret = key_event[i].fptr(event, game);
	i++;
      }
  return (ret);
}
