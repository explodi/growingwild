all:
	g++ -o build/growingwild src/main.cpp src/Cat.cpp src/Timer.cpp `sdl2-config --cflags --libs` -lBox2D
