#include "epikong_sdl.h"

void		move_x(t_game *game, t_tile env[7], int *x, int *y)
{
  *x = game->player.pos[X] + ((game->player.direction_x == RIGHT) ? 1 : -1);
  *y = game->player.pos[Y];
  env[6] = game->map->data[*y][*x];
  if (env[6] != WALL)
    game->player.pos[X] += game->player.direction_x;
}

void		move_y(t_game *game, t_tile env[7], int *x, int *y)
{
  if (game->player.direction_y == UP)
    {
      env[6] = game->map->data[*y - 1][*x];
      env[5] = game->map->data[*y][*x];
      if (env[5] == LADDER && env[6] != WALL)
	game->player.pos[Y] += game->player.direction_y;
    }
  else if (game->player.direction_y == DOWN)
    {
      env[6] = game->map->data[*y][*x];
      env[5] = game->map->data[*y + 1][*x];
      if (env[5] != WALL)
	game->player.pos[Y] += game->player.direction_y;
    }
}

void		check_gravity(t_game *game, int *x, int *y)
{
  int		maxfall;

  maxfall = 0;
  if (game->player.fall == 0)
    game->player.fall = 1;
  else
    game->player.fall = (game->player.fall >= 4) ? 16 : game->player.fall * 2;
  maxfall = 0;
  while (game->map->data[*y + maxfall][*x] == EMPTY)
    maxfall++;
  if (game->player.fall >= maxfall)
    {
      game->player.pos[Y] += maxfall - 1;
      game->player.fall = 0;
    }
  else
    game->player.pos[Y] += game->player.fall;
}

void		get_env(t_game *game, t_tile env[7], int *x, int *y)
{
  *x = game->player.pos[X];
  *y = game->player.pos[Y];
  env[0] = game->map->data[*y - 1][*x];
  env[1] = game->map->data[*y][*x - 1];
  env[2] = game->map->data[*y][*x];
  env[3] = game->map->data[*y][*x + 1];
  env[4] = game->map->data[*y + 1][*x];
}

void		move_player(t_game *game)
{
  int		x;
  int		y;
  t_tile	env[7];

  get_env(game, env, &x, &y);
  if (game->player.jump != 0)
    {
      do_jump(game, x, y);
      return ;
    }
  if (game->player.direction_x != STOP)
    move_x(game, env, &x, &y);
  env[5] = game->map->data[y + 1][x];
  env[6] = game->map->data[y][x];
  if (env[5] == EMPTY && env[6] != LADDER)
    check_gravity(game, &x, &y);
  else
    game->player.fall = 0;
  y = game->player.pos[Y];
  x = game->player.pos[X];
  move_y(game, env, &x, &y);
}
