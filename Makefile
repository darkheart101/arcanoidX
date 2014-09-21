all:
	g++ -o arc main.cpp collide.cpp collide.h misc.cpp misc.h level.cpp level.h -lSDL -lSDL_image
