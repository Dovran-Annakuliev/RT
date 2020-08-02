GCC = gcc -Wall -Wextra -Werror
NAME = RTv1
SRCS = sources/main.c
OBJS = $(SRCS:.c=.o)
HEAD = -c -I includes\rtv1.h

ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname)
endif
ifeq ($(detected_OS),Linux)
	#LIB += -L./libs/glad/ -lglad -ldl  -lGL -L./libs/glfw/src/ -lglfw3 \
	-lXrandr -lXrender -lXi -lXfixes -lXxf86vm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp
#	LIBMAKE := minilibx/minilibx
#	LIB :=  -L libft -lft -L $(LIBMAKE) -lmlx_Linux  -lXrandr -lXrender -lXi -lXfixes \
#	-lXxf86vm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lm -lOpenCL -lrt
	LIB :=  -L libft -lft -L -lXrandr -lXrender -lXi -lXfixes \
    	-lXxf86vm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lm -lOpenCL -lrt
endif
ifeq ($(detected_OS),Darwin)  
	#LIB = -L./libs/glad/ -lglad -L./libs/glfw/src/ -lglfw3      # Mac OS X
	#LIBRARIES += -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
#	LIBMAKE := minilibx/minilibx_macos
#	LIB = -L libft -lft -L $(LIBMAKE) -lmlx -framework OpenGL -framework Appkit -framework OpenCL
	LIB = -L libft -lft -L -framework OpenGL -framework Appkit -framework OpenCL
endif

all: $(NAME)

sources%.o: %.c
		$(GCC) -c $<

lib:
		make -C libft
		cd sdl && ./configure && make && make install

$(NAME): $(OBJS) lib
		 $(GCC) $(OBJS)  $(LIB)   -o $(NAME)

clean:
		rm -f $(OBJS)
		make -C libft clean

fclean: clean
		rm -f $(NAME)
		make -C libft fclean
		cd sdl && make clean

re: fclean all
