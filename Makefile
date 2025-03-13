main:
	g++ -std=c++11 Sources/*.cpp -o RandomWalk \
	-I Headers \
	-I /opt/homebrew/include/SDL2 \
	-I /opt/homebrew/opt/sdl2/include \
	-I /opt/homebrew/opt/sdl2_ttf/include \
	-L /opt/homebrew/lib \
	-lSDL2 -lSDL2_ttf
run:
	./RandomWalk
