/*
** epikong.c for main in /home/batema_j/rendu/T2Rush1/etape_1
**
** Made by Jean-Yves Bateman
** Login   <batema_j@epitech.net>
**
** Started on  Fri Mar  7 22:10:41 2014
** Last update Sun Mar  9 16:42:29 2014 BLANCHARD
*/

#include "epikong.h"
#include "epikong_sdl.h"

void		reset_game(t_game *game)
{
  if (game->background)
    SDL_FreeSurface(game->background);
  game->background = NULL;
  if (game->enemies)
    free(game->enemies);
  game->enemies = NULL;
}

int		prepare_exit(t_game *game, int ret)
{
  int		i;

  i = 0;
  reset_game(game);
  if (game->images)
    while (i < NB_IMAGES)
      SDL_FreeSurface(game->images[i++]);
  if (game->maps_list)
    free(game->maps_list);
  SDL_Quit();
  return (ret);
}

int		get_maps(char *dir, char *maps[5])
{
  char		c;
  int		i;
  char		*str;

  i = 0;
  if (!(str = malloc(strlen(dir) + 6)))
    return (_error(strdup("get_maps : malloc fail")));
  strcat(str, dir);
  strcat(str, "/menu");
  if (open(str, O_RDONLY) == -1)
    return (_error(strdup("get_maps : menu not found")));
  while (i < 5)
    {
      c = '0' + i;
      if (!(maps[i] = malloc(strlen(dir) + 6)))
	return (_error(strdup("get_maps : malloc fail")));
      strcat(maps[i], dir);
      strcat(maps[i], "/map");
      maps[i][strlen(dir) + 4] = c;
      i++;
    }
  free(str);
  return (0);
}

int		main(int ac, char **av)
{
  t_game	game;
  char		*maps[5];
  int		ret;
  int		i;

  i = 0;
  if (ac == 2)
    ret = get_maps(av[1], maps);
  else
    ret = get_maps("maps", maps);
  if (ret == -1)
    return (-1);
  if (init_game(&game, 5, maps) == -1)
    return (prepare_exit(&game, -1));
  game.flag = CONTINUE;
  while (game.flag == CONTINUE)
    {
      if (init_map(&game) == -1)
  	return (prepare_exit(&game, -1));
      play(&game);
      reset_game(&game);
    }
  while (i < 6)
    free(maps[i++]);
  return (prepare_exit(&game, 0));
}
