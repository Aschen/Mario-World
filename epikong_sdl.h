/*
** epikong_sdl.h for epikong in /home/blanch_d/T2Rush1/etape_1
**
** Made by BLANCHARD
** Login   <blanch_d@epitech.net>
**
** Started on  Sat Mar  8 16:25:32 2014 BLANCHARD
** Last update Sun Mar  9 16:33:22 2014 BLANCHARD
*/

#ifndef EPIKONG_SDL_H_
# define EPIKONG_SDL_H_

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <sys/types.h>
# include <dirent.h>
# include "epikong.h"

# define BACKGROUND_X	1600
# define BACKGROUND_Y	1200
# define NB_IMAGES	10
# define SIZE_IMAGE	50
# define MAX_WIDTH	1900
# define MAX_HEIGHT	1000
# define LEFT		-1
# define STOP		0
# define RIGHT		1
# define DOWN		1
# define UP		-1
# define X		0
# define Y		1
# define MENU		0
# define PLAY		1
# define CONTINUE	1
# define QUIT		2
# define EVENTS		7
# define PLEFT		0
# define PRIGHT		1

typedef struct  s_player
{
  SDL_Surface	*sprites[2];
  SDL_Surface	*sprite;
  int		pos[2];
  int		direction_x;
  int		direction_y;
  int		fall;
  int		para;
  int		jump;
  int		dist;
}               t_player;

typedef struct  s_enemy
{
  SDL_Surface	*sprite;
  SDL_Surface	*sprites[2];
  int		pos[2];
  int		direction;
}               t_enemy;

typedef struct	s_game
{
  SDL_Surface	*screen;
  SDL_Surface	*images[NB_IMAGES];
  SDL_Surface	*background;
  t_player	player;
  t_enemy	*enemies;
  t_map		**maps_list;
  t_map		*map;
  int		size_tile;
  int		current;
  int		flag;
}		t_game;


typedef int (*action)(SDL_Event *event, t_game*);

typedef struct  s_event_handler
{
    action      fptr;
    Uint32      key_code;
}               t_event_handler;


/*
 * fail sdl
 */
SDL_Surface	*rotozoomSurfaceXY(SDL_Surface *, double, double, double, int);

/*
 * sdl_load_map.c
 */
int		init_player(t_game *game, Uint32 x, Uint32 y);
int		init_enemy(t_game *game, Uint32 x, Uint32 y, int nb);
int		init_sprites(t_game *game);
int		init_tiles(t_game *game);
int		init_map(t_game *game);

/*
 * sdl_load_map_2.c
 */
int		load_background(t_game *game);

/*
 * sdl_init.c
 */
int		load_images(t_game *game);
int		init_base(t_game *game);
int		get_size_tile(int size_x_map, int size_y_map);
int		init_game(t_game *game, int ac, char **av);

/*
 * play.c
 */
void		do_jump(t_game *game, int x, int y);
int		play(t_game *game);

/*
 * sdl_refresh.c
 */
int		refresh_sprites(t_game *game);

/*
 * sdl_event.c
 */
int		hook_event(SDL_Event *event, t_game *game);

/*
 * sdl_event_2.c
 */
int		key_escape(SDL_Event *event, t_game *game);
int		key_space(SDL_Event *event, t_game *game);
int		key_right(SDL_Event *event, t_game *game);
int		key_left(SDL_Event *event, t_game *game);
int		key_up(SDL_Event *event, t_game *game);

/*
 * player.c
 */
void		move_player(t_game *game);

int		_error(char*);
void		*__error(char*);
int		prepare_exit(t_game *game, int ret);
int		hook_event(SDL_Event *event, t_game *game);
void		display(t_map *info);

#endif /* !EPIKONG_SDL_H_ */
