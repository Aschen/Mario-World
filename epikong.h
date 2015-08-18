#ifndef EPIKONG_H_
# define EPIKONG_H_

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>

# define MAX_X	1000
# define MAX_Y	1000

typedef enum	e_tile
  {
    EMPTY = 0,
    WALL,
    LADDER,
    LMOB,
    EXIT,
    ENTER,
    KEY,
    LPLAYER,
    RPLAYER,
    RMOB
  }		t_tile;

typedef struct	s_map
{
  char		**data;	// Map
  int		**c_map;
  Uint32	x;	// Largeur
  Uint32	y;	// Hauteur
  char		obj[7];
  int		enemies;
}		t_map;

void		fill_map(t_map *info, FILE *fd);
int		store_map(Uint32 size, Uint32 line, t_map *info, FILE *fd);
int		get_info(char *map, t_map *info);
void		init_strt(t_map *info);
int		play_map(t_map *map);
void	        set_paths(t_map *info);
void		get_pos(t_map *info);
void		check_map_play(t_map *info, Uint32 x, Uint32 y);
void		set_jump(t_map *info, Uint32 x, Uint32 y);
void		check_map_pos(t_map *info);
void		check_map_objs(t_map *info);

#endif /* !_EPIKONG_H_ */
