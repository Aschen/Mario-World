CC	= gcc

RM	= rm -rf

SRCS	= main.c \
	  get_map.c \
	  sdl_init.c \
	  sdl_load_map.c \
	  sdl_load_map_2.c \
	  error.c \
	  misc.c \
	  play.c \
	  sdl_event.c \
	  sdl_event_2.c\
	  sdl_refresh.c \
	  player.c \
	  player_jump.c \
	  load_map.c \

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -W -Wall -Wextra

CFLAGS += `sdl-config --cflags`

NAME	= epikong

all:		$(NAME)
		@echo -e " [0;32m =============================================================== [0;0m "

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) `sdl-config --libs` -lSDL_gfx -lSDL2_ttf -lSDL_image

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
