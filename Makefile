all: compile run


compile: src/main.cpp
	g++ src/main.cpp  src/Snake.cpp -o sfml-app -I ~/SFML-2.5.1/include  -I ~/tetris/ -L ~/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system 


run sfml-app:
	./sfml-app

export:
	export LD_LIBRARY_PATH=~/SFML-2.5.1/lib && ./sfml-app
