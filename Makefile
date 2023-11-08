all:
	g++ -std=c++17 -Iinclude/sdl -Llibs -o build/Build.exe main.cpp src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
