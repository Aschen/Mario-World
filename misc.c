#include "epikong_sdl.h"

int	_error(char *str)
{
  if (str)
    {
      fprintf(stderr, "%s : %s\n", str, SDL_GetError());
      free(str);
    }
  else
    fprintf(stderr, "%s : %s\n", "Error", SDL_GetError());
  return (-1);
}

void	*__error(char *str)
{
  if (str)
    {
      fprintf(stderr, "%s : %s\n", str, SDL_GetError());
      free(str);
    }
  else
    fprintf(stderr, "%s : %s\n", "Error", SDL_GetError());
  return (NULL);
}

