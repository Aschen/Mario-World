#include "epikong_sdl.h"

void		do_jump_up(t_game *game, int pos[2])
{
  if (game->player.jump == 2)
    {
      game->player.dist = 0;
      if (game->map->data[pos[Y] - 1][pos[X]] != WALL)
	{
	  game->player.dist++;
	  if (game->map->data[pos[Y] - 2][pos[X]] != WALL)
	    game->player.dist++;
	  game->player.pos[Y] -= game->player.dist;
	}
      else
	game->player.jump = 0;
    }
  else if (game->map->data[pos[Y]][pos[X]] != LADDER)
    {
      game->player.pos[Y] += game->player.dist;
    }
}

void		do_jump_left(t_game *game, int pos[2])
{
  if (game->player.jump == 12)
    {
      game->player.pos[Y] -= 1;
      game->player.pos[X] -= 2;
    }
  else if (game->map->data[pos[Y]][pos[X]] != LADDER)
    {
      game->player.pos[Y] -= 1;
    }
}

void		do_jump_right(t_game *game, int pos[2])
{
  if (game->player.jump == 12)
    {
      game->player.pos[Y] -= 1;
      game->player.pos[X] += 2;
    }
  else if (game->map->data[pos[Y]][pos[X]] != LADDER)
    {
      game->player.pos[Y] -= 1;
    }
}

void		do_jump(t_game *game, int x, int y)
{
  int		pos[2];

  pos[X] = x;
  pos[Y] = y;
  if (game->player.jump == 1 || game->player.jump == 2)
    do_jump_up(game, pos);
  if (game->player.jump == 21 || game->player.jump == 22)
    do_jump_left(game, pos);
  if (game->player.jump == 11 || game->player.jump == 12)
    do_jump_right(game, pos);
  game->player.jump--;
  if (game->player.jump % 10 == 0)
    game->player.jump = 0;
}
